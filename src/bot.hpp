#pragma once

#include <memory>

#include "log/logger.hpp"
#include "blocking_request.hpp"
#include "comm/comm_client.hpp"

extern "C"
{
#include <vm/process.h>
}

namespace caio
{
	class bot final
	{
	public:
		enum class status
		{
			ok, dead, disconnected
		};

		const size_t MAX_MEMORY = 200*1024; // 200 kB

		bot(std::unique_ptr<comm_client> comm_client);
		~bot();
		
		status tick(c_cpu_handle cpu);
		void reset();

		void set_target(int x, int y);
		
	private:
		logger& m_logger;
		std::unique_ptr<comm_client> m_comm_client;
		blocking_request m_current_blocking_request;

		bool m_is_alive;

		c_process_t m_vm_process;
	};
}
