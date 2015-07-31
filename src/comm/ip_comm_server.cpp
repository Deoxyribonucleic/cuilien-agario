#include "ip_comm_server.hpp"

#include <functional>

using namespace caio;

ip_comm_server::ip_comm_server(unsigned short port)
	: m_logger(logger::get("ip-server")),
	m_port(port),
	m_acceptor(m_io_service, boost::asio::ip::tcp::endpoint(
				boost::asio::ip::tcp::v4(), port)),
	m_socket(m_io_service)
{
	m_logger.info() << "starting..." << std::endl;
	m_thread = std::thread(std::bind(&ip_comm_server::thread_func, this));
	m_logger.info() << "started" << std::endl;
}

ip_comm_server::~ip_comm_server()
{
	m_logger.info() << "stopping..." << std::endl;
	m_io_service.stop();
	m_thread.join();
	m_logger.info() << "stopped" << std::endl;
}

void ip_comm_server::accept(
		std::vector<std::unique_ptr<comm_client>>& out)
{
	std::lock_guard<std::mutex> guard(m_lock);
	for(auto &client: m_accept_queue)
	{
		out.push_back(std::move(client));
	}
	m_accept_queue.clear();
}

void ip_comm_server::thread_func()
{
	logger::set_thread_name("COMM");
	m_logger.info() << "comm thread started" << std::endl;

	start_accept();
	m_io_service.run();

	m_logger.info() << "comm thread stopped" << std::endl;
}

void ip_comm_server::start_accept()
{
	m_acceptor.async_accept(m_socket,
			std::bind(&ip_comm_server::handle_accept, this));
}

void ip_comm_server::handle_accept()
{
	m_logger.info() << "incoming connection from " << m_socket.remote_endpoint() << std::endl;
	
	std::lock_guard<std::mutex> guard(m_lock);
	m_accept_queue.push_back(std::make_unique<ip_comm_client>(std::move(m_socket)));
	
	start_accept();
}

