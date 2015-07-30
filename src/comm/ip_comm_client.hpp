#pragma once

#include "comm_client.hpp"

namespace caio
{
	class ip_comm_client final : public comm_client
	{
	public:
		ip_comm_client();
		~ip_comm_client();
	};
}
