#pragma once

#include <boost/asio.hpp>

#include "comm_client.hpp"

namespace caio
{
	class ip_comm_client final : public comm_client
	{
	public:
		ip_comm_client(boost::asio::io_service& io_service);
		~ip_comm_client();

		boost::asio::ip::tcp::socket& get_socket();

		bool is_connected() const;

	private:
		bool m_connected;
		boost::asio::ip::tcp::socket m_socket;
	};
}
