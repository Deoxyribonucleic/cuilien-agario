#pragma once

#include <boost/asio.hpp>

#include <dawn/data/buffer.hpp>

#include "log/logger.hpp"
#include "comm_client.hpp"
#include "json_message_parser.hpp"
#include "message.hpp"

namespace caio
{
	class ip_comm_client final : public comm_client
	{
	public:
		ip_comm_client(boost::asio::ip::tcp::socket socket);
		~ip_comm_client();

		boost::asio::ip::tcp::socket& get_socket();

		bool is_connected() const;

		void send_message(message const& msg);

	private:
		void start_read();
		void handle_read(boost::system::error_code error, size_t length);

		void handler(boost::system::error_code const&, std::size_t);

		void parse_buffer_data();
		void parse_update();


		logger& m_logger;
		dawn::data::buffer m_buffer;
		bool m_connected;
		boost::asio::ip::tcp::socket m_socket;
		size_t m_recvLength;
		json_message_parser m_message_parser;
	};
}
