#include "ivt.hpp"
#include "bot.hpp"

using namespace caio;

void random(c_cpu_t* cpu)
{
	cpu->context->reg.a = rand();
}

void set_target(c_cpu_handle cpu)
{
	reinterpret_cast<bot*>(cpu->context->user_context)->set_target(
			cpu->context->reg.a, cpu->context->reg.b);
}

c_interrupt_handler_t handlers[] = {
	random,
	set_target
};

c_interrupt_vector_table_t table = {
	handlers,
	sizeof(handlers) / sizeof(c_interrupt_handler_t)
};

c_interrupt_vector_table_t ivt::build()
{
	return table;
}

