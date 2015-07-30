#include <iostream>
#include <memory>

#include "log/logger.hpp"
#include "comm/ip_comm_server.hpp"

using namespace caio;

int main()
{
	logger::set_thread_name("MAIN");
	logger::get("main").info() << "cuilien agar.io brain" << std::endl;
	logger::get("main").info() << "initializing..." << std::endl;

	std::unique_ptr<caio::ip_comm_server> server = std::make_unique<caio::ip_comm_server>(12314);

	logger::get("main").info() << "goodbye" << std::endl;
	return 0;
}
