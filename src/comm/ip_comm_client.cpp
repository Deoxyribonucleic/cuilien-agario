#include "ip_comm_client.hpp"

#include <iostream>

using namespace caio;

ip_comm_client::ip_comm_client(boost::asio::ip::tcp::socket socket)
	: m_logger(logger::get("ip-client/" + std::to_string((long)this))),
	m_connected(true),
	m_socket(std::move(socket))
{
	m_logger.info() << "connected from " << m_socket.remote_endpoint() << std::endl;
	start_read();
}

ip_comm_client::~ip_comm_client()
{
}

boost::asio::ip::tcp::socket& ip_comm_client::get_socket()
{
	return m_socket;
}

bool ip_comm_client::is_connected() const
{
	return m_connected;
}

void ip_comm_client::start_read()
{
	m_socket.async_read_some(
			boost::asio::buffer(m_buffer, 1),
			std::bind(&ip_comm_client::handle_read,
				this,
				std::placeholders::_1,
				std::placeholders::_2));
}

void ip_comm_client::handle_read(boost::system::error_code error, size_t length)
{
	if(error)
	{
		m_logger.info() << "disconnected" << std::endl;
		m_connected = false;
		return;
	}

	std::cout << m_buffer[0] << std::endl;
	start_read();
}

