#include "comm_client.hpp"

using namespace caio;

comm_client::comm_client()
{
}

comm_client::~comm_client()
{
}

std::unique_ptr<message> comm_client::pop_message()
{
	std::lock_guard<std::mutex>_(m_lock);
	
	if(m_msg_queue.size() == 0)
		return std::unique_ptr<message>(nullptr);

	auto message = std::move(m_msg_queue.front());
	m_msg_queue.pop();
	return message;
}

void comm_client::queue_message(std::unique_ptr<message> msg)
{
	std::lock_guard<std::mutex>_(m_lock);
	m_msg_queue.push(std::move(msg));
}
