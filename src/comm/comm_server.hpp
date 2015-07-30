#pragma once

#include <vector>
#include <memory>

#include "comm_client.hpp"

namespace caio
{
	class comm_server
	{
	public:
		comm_server();
		virtual ~comm_server();
		
		virtual std::vector<std::unique_ptr<comm_client>> listen() = 0;
	};
}
