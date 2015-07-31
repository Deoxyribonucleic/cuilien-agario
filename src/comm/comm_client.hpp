#pragma once

namespace caio
{
	class comm_client
	{
	public:
		comm_client();
		virtual ~comm_client();

		virtual bool is_connected() const = 0;
	};
}
