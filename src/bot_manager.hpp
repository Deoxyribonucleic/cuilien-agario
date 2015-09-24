#pragma once

#include <memory>
#include <queue>

#include "comm/comm_client.hpp"
#include "bot.hpp"

#include <vm/cpu.h>

namespace caio
{
	class bot_manager final
	{
	public:
		bot_manager();
		~bot_manager();

		void tick(c_cpu_handle cpu);
		void create_new_bot(std::unique_ptr<comm_client> client);

	private:
		std::queue<std::unique_ptr<bot>> m_bots;
	};
}
