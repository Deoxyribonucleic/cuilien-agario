#include "bot.hpp"

#include <iostream>

using namespace caio;

bot::bot(std::unique_ptr<comm_client> comm_client)
	: m_logger(logger::get("bot/" + std::to_string((long)this))),
	m_comm_client(std::move(comm_client)),
	m_current_blocking_request(blocking_request::none)
{
	m_logger.info() << "new bot :] " << m_comm_client.get() << std::endl;
}

bot::~bot()
{
	m_logger.info() << "bot ded :[" << std::endl;
}

bot::status bot::tick()
{
	if(!m_comm_client->is_connected())
		return bot::status::disconnected;

	std::unique_ptr<message> msg;
	while((msg = m_comm_client->pop_message()))
	{
		if(msg->opcode() == message::type::ready)
		{
			m_logger.info() << "client ready; sending spawn command" << std::endl;
			m_comm_client->send_message(respawn_message());
		}
	}

	return bot::status::ok;
}

