#include "ip_comm_server.hpp"

using namespace caio;

ip_comm_server::ip_comm_server(unsigned short port)
	: m_port(port)
{
	// open listener
}

ip_comm_server::~ip_comm_server()
{
	// close listener
}

std::vector<std::unique_ptr<comm_client>> ip_comm_server::listen()
{
	std::vector<std::unique_ptr<comm_client>> new_clients;
	
	// TODO: listen :3

	return new_clients;
}

