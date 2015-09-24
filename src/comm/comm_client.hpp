#pragma once

#include "message.hpp"

#include <memory>
#include <queue>
#include <mutex>

namespace caio
{
	class comm_client
	{
	public:
		comm_client();
		virtual ~comm_client();

		virtual bool is_connected() const = 0;

		std::unique_ptr<message> pop_message();
		virtual void send_message(message const& msg) = 0;

	protected:
		void queue_message(std::unique_ptr<message> msg);

	private:
		std::mutex m_lock;
		std::queue<std::unique_ptr<message>> m_msg_queue;
	};
}

