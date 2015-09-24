#pragma once

extern "C"
{
#include <vm/cpu.h>
}

namespace caio
{
	class ivt
	{
	public:
		static c_interrupt_vector_table_t build();
	};
}
