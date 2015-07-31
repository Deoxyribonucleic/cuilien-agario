#include <iostream>
#include <memory>
#include <signal.h>

#include "log/logger.hpp"
#include "comm/ip_comm_server.hpp"

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
		std::unique_ptr<caio::ip_comm_server> server = std::make_unique<caio::ip_comm_server>(12314);
		logger::get("main").info() << "initialized" << std::endl;

		while(!stop)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
