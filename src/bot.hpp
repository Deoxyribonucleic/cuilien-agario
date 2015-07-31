#pragma once

#include <memory>

#include "log/logger.hpp"
#include "blocking_request.hpp"
#include "comm/comm_client.hpp"

namespace caio
{
	class bot final
	{
	public:
		enum class status
		{
			ok, dead, disconnected
		};

		bot(std::unique_ptr<comm_client> comm_client);
		~bot();
		
		status tick();
		
	private:
		logger& m_logger;
		std::unique_ptr<comm_client> m_comm_client;
		blocking_request m_current_blocking_request;
	};
}
