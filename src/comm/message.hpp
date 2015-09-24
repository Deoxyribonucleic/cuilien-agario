#pragma once

namespace caio
{
	struct message
	{
		message();
		virtual ~message();

		enum struct type : int
		{
			ready = 1,
			respawn = 2,
			death = 3,
			update = 4,
			set_target = 5,
			spawned = 6
		};

		virtual type opcode() const = 0;
	};
	
	struct ready_message : message
	{
		type opcode() const { return type::ready; }
	};
	
	struct respawn_message : message
	{
		type opcode() const { return type::respawn; }
	};
	
	struct death_message : message
	{
		type opcode() const { return type::death; }
	};

	struct set_target_message : message
	{
		type opcode() const { return type::set_target; }
		set_target_message(int x, int y) : x(x), y(y) {}
		int x, y;
	};
	
	struct spawned_message : message
	{
		type opcode() const { return type::spawned; }
	};
}

