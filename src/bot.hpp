#pragma once

#include "blocking_request.hpp"

namespace caio
{
	class bot final
	{
	public:
		bot();
		~bot();

		
	private:
		blocking_request m_current_blocking_request;
	};
}
