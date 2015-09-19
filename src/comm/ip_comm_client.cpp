#include "ip_comm_client.hpp"

#include <iostream>

#include <dawn/data/integral.hpp>

using namespace caio;

ip_comm_client::ip_comm_client(boost::asio::ip::tcp::socket socket)
	: m_logger(logger::get("ip-client/" + std::to_string((long)this))),
	m_recvLength(0),
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
	size_t length = m_recvLength;
	if(length == 0)
	{
		length = 2;
	}
	
	m_buffer = dawn::data::buffer(length);

	boost::asio::async_read(
			m_socket,
			boost::asio::buffer(m_buffer.data(), length),
			std::bind(&ip_comm_client::handle_read,
				this,
				std::placeholders::_1,
				std::placeholders::_2));
}

void ip_comm_client::handle_read(boost::system::error_code error, size_t length)
{
	m_logger.info() << "got " << length << " bytes / " << m_recvLength << std::endl;

	if(error ||
			(!(m_recvLength == 0 && length == 2) &&
			m_recvLength != length))
	{
		m_logger.info() << "disconnected" << std::endl;
		m_connected = false;
		return;
	}

	// if recvLength is 0 we have received the length header
	if(m_recvLength == 0)
	{
		dawn::data::uint16 length;
		length.deserialize(m_buffer);
		m_recvLength = *length;

		m_logger.info() << "length header: " << *length << std::endl;
	}
	else
	{
		m_recvLength = 0;
	}

	start_read();
}

