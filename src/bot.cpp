#include "bot.hpp"

extern "C"
{
#include <vm/cpu.h>
#include <vm/mem.h>
#include <vm/error.h>
}

#include <iostream>

using namespace caio;

bot::bot(std::unique_ptr<comm_client> comm_client)
	: m_logger(logger::get("bot/" + std::to_string((long)this))),
	m_comm_client(std::move(comm_client)),
	m_current_blocking_request(blocking_request::none),
	m_is_alive(false)
{
	m_logger.info() << "new bot :] " << m_comm_client.get() << std::endl;

	// zero out registers
	memset(&m_vm_process.context.reg, 0, sizeof(m_vm_process.context.reg));
	m_vm_process.context.reg.ip = 0x0c;
	m_vm_process.context.reg.sp = 0xFFFFFF00;

	m_vm_process.context.user_context = this;

	m_vm_process.context.memory = c_mem_init(bot::MAX_MEMORY);
	int seed_length = c_mem_load_file(m_vm_process.context.memory, "seed.cx", m_vm_process.context.reg.ip);
	if(seed_length == 0)
	{
		m_logger.error() << "failed to load seed" << std::endl;
	}
	
	reset();
}

bot::~bot()
{
	c_mem_free(m_vm_process.context.memory);
	m_logger.info() << "bot ded :[" << std::endl;
}

bot::status bot::tick(c_cpu_handle cpu)
{
	if(!m_comm_client->is_connected())
		return bot::status::disconnected;

	std::unique_ptr<message> msg;
	while((msg = m_comm_client->pop_message()))
	{
		switch(msg->opcode())
		{
		case message::type::ready:
			m_logger.info() << "client ready; sending spawn command" << std::endl;
			m_comm_client->send_message(respawn_message());
			break;
		case message::type::spawned:
			m_is_alive = true;
			break;
		case message::type::death:
			m_logger.info() << "bot dead" << std::endl;
			m_is_alive = false;
			return bot::status::dead;
		default:;
		}
	}
	
	// run time slice
	if(m_is_alive)
	{
		cpu->context = &m_vm_process.context;
		for(int step = 0; step < 100; ++step)
		{
			c_cpu_step(cpu);
		}
	}

	return bot::status::ok;
}

void bot::reset()
{
	m_vm_process.context.reg.ip = 0x0c;
	m_comm_client->send_message(respawn_message());
}

void bot::set_target(int x, int y)
{
	m_comm_client->send_message(set_target_message {x, y});
}

