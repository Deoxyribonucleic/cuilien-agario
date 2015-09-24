#include "bot_manager.hpp"

using namespace caio;

bot_manager::bot_manager()
{
}

bot_manager::~bot_manager()
{
}

void bot_manager::tick(c_cpu_handle cpu)
{
	if(m_bots.empty())
		return;

	auto bot = std::move(m_bots.front());
	m_bots.pop();

	bot::status bot_status = bot->tick(cpu);

	// if the bot is disconnected, don't put it back in the queue
	if(bot_status == bot::status::disconnected)
		return;

	if(bot_status == bot::status::dead)
	{
		// reset bot with mutated version of best bot so far
		bot->reset();
	}

	m_bots.push(std::move(bot));
}

void bot_manager::create_new_bot(std::unique_ptr<comm_client> client)
{
	m_bots.push(std::make_unique<bot>(std::move(client)));
}

