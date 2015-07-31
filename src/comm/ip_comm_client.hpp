#pragma once

#include <boost/asio.hpp>

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
		char m_buffer[1];
		bool m_connected;
		boost::asio::ip::tcp::socket m_socket;
	};
}
