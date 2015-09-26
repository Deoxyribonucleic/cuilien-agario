#include <iostream>
#include <memory>
#include <signal.h>
#include <functional>

#include "log/logger.hpp"
#include "comm/ip_comm_server.hpp"
#include "bot_manager.hpp"
#include "ivt.hpp"
#include "config.hpp"

extern "C"
{
#include <vm/error.h>
#include <vm/cpu.h>
#include <vm/instr.h>
}

using namespace caio;


bool stop = false;

void signal_handler(int signal)
{
	if(signal == SIGINT)
	{
		stop = true;
	}
}

int main()
{
	srand(time(NULL));

	logger::set_thread_name("MAIN");
	logger::get("main").info() << "cuilien agar.io brain" << std::endl;
	
	signal(SIGINT, signal_handler);

	config cfg;
	if (cfg.load_config("config.json")) {
		logger::get("main").info() << "Config file 'config.json' loaded" << std::endl;
	}

	try
	{
		logger::get("main").info() << "initializing..." << std::endl;

		logger::get("main").info() << "initializing vm..." << std::endl;
		int error;
		c_cpu_handle cpu;
		cpu = c_cpu_init();
		if(c_error_last)
		{
			c_error_print(c_error_last);
			return 1;
		}
		
		logger::get("main").info() << "disabling a few opcodes..." << std::endl;
		c_instruction_vector[C_INSTR_PUTC] = NULL;
		c_instruction_vector[C_INSTR_GETC] = NULL;
		//c_instruction_vector[C_INSTR_SHOW] = NULL;

		logger::get("main").info() << "initializing ivt..." << std::endl;
		cpu->ivt = ivt::build();

		logger::get("main").info() << "initializing comms server..." << std::endl;
		caio::ip_comm_server server(12314);

		logger::get("main").info() << "initializing bot manager..." << std::endl;
		caio::bot_manager bot_mgr;
		
		logger::get("main").info() << "initialized" << std::endl;

		while(!stop)
		{
			bot_mgr.tick(cpu);
			
			std::vector<std::unique_ptr<comm_client>> new_clients;
			server.accept(new_clients);
			
			for(auto& client: new_clients)
			{
				bot_mgr.create_new_bot(std::move(client));
			}
		}

		logger::get("main").info() << "shutting down..." << std::endl;

		c_cpu_free(cpu);
	}
	catch(std::exception& e)
	{
		logger::get("main").fatal() << "unhandled exception: " << e.what() << std::endl;
	}

	logger::get("main").info() << "shut down" << std::endl;
	logger::get("main").info() << "goodbye" << std::endl;
	return 0;
}
