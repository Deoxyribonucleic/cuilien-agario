#pragma once

#include <boost/asio.hpp>

#include <dawn/data/buffer.hpp>

#include "log/logger.hpp"
#include "comm_client.hpp"

namespace caio
{
	class ip_comm_client final : public comm_client
	{
	public:
		ip_comm_client(boost::asio::ip::tcp::socket socket);
		~ip_comm_client();

		boost::asio::ip::tcp::socket& get_socket();

		bool is_connected() const;

	private:
		void start_read();
		void handle_read(boost::system::error_code error, size_t length);
		

		logger& m_logger;
		dawn::data::buffer m_buffer;
		bool m_connected;
		boost::asio::ip::tcp::socket m_socket;
		size_t m_recvLength;
	};
}
