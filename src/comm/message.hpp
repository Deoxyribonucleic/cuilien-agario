#pragma once

namespace caio
{
	class message
	{
	public:
		message();
		virtual ~message();

		enum class type : int
		{
			ready = 1,
			respawn,
			update
		};

		virtual type opcode() const = 0;
	};
	
	class ready_message : public message
	{
	public:
		type opcode() const { return type::ready; }
	};
	
	class respawn_message : public message
	{
	public:
		type opcode() const { return type::respawn; }
	};
}

