#include <iostream>
#include <memory>
#include <signal.h>

#include "log/logger.hpp"
#include "comm/ip_comm_server.hpp"
#include "bot_manager.hpp"

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
	logger::set_thread_name("MAIN");
	logger::get("main").info() << "cuilien agar.io brain" << std::endl;
	
	signal(SIGINT, signal_handler);

	try
	{
		logger::get("main").info() << "initializing..." << std::endl;

		caio::ip_comm_server server(12314);
		caio::bot_manager bot_mgr;
		
		logger::get("main").info() << "initialized" << std::endl;

		while(!stop)
		{
			bot_mgr.tick();
			
			std::vector<std::unique_ptr<comm_client>> new_clients;
			server.accept(new_clients);
			
			for(auto& client: new_clients)
			{
				bot_mgr.create_new_bot(std::move(client));
			}
		}

		logger::get("main").info() << "shutting down..." << std::endl;
	}
	catch(std::exception& e)
	{
		logger::get("main").fatal() << "unhandled exception: " << e.what() << std::endl;
	}

	logger::get("main").info() << "shut down" << std::endl;
	logger::get("main").info() << "goodbye" << std::endl;
	return 0;
}
