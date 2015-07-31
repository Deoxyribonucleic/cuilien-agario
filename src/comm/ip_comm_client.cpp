#include "ip_comm_client.hpp"

#include <iostream>

using namespace caio;

ip_comm_client::ip_comm_client(boost::asio::io_service& io_service)
	: m_connected(true), m_socket(io_service)
{
}

ip_comm_client::~ip_comm_client()
{
	std::cout << "Ouch\n"; 
}

boost::asio::ip::tcp::socket& ip_comm_client::get_socket()
{
	return m_socket;
}

bool ip_comm_client::is_connected() const
{
	return m_connected;
}

