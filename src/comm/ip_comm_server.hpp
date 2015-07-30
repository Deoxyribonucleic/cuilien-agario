#pragma once

#include "comm_server.hpp"
#include "ip_comm_client.hpp"

namespace caio
{
	class ip_comm_server final : public comm_server
	{
	public:
		ip_comm_server(unsigned short port);
		~ip_comm_server();

		std::vector<std::unique_ptr<comm_client>> listen();

	private:
		unsigned short m_port;
	};
}
