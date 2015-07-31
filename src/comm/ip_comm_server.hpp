#pragma once

#include <thread>
#include <mutex>

#include <boost/asio.hpp>

#include "log/logger.hpp"
#include "comm_server.hpp"
#include "ip_comm_client.hpp"

namespace caio
{
	class ip_comm_server final : public comm_server
	{
	public:
		ip_comm_server(unsigned short port);
		~ip_comm_server();

		void accept(std::vector<std::unique_ptr<comm_client>>& out);

	private:
		void thread_func();

		void start_accept();
		void handle_accept();
		
		logger& m_logger;

		unsigned short m_port;

		std::mutex m_lock;
		std::thread m_thread;
		boost::asio::io_service m_io_service;
		boost::asio::ip::tcp::acceptor m_acceptor;
		boost::asio::ip::tcp::socket m_socket;
		
		std::vector<std::unique_ptr<ip_comm_client>> m_accept_queue;
	};
}
