#pragma once

#include <memory>
#include <string>

#include "message.hpp"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace caio
{
	class json_message_parser final
	{
	public:
		typedef rapidjson::Writer<rapidjson::StringBuffer> json_writer;
		std::unique_ptr<message> parse(std::string const& str) const;

		std::string build(message const& msg) const;

	private:
		std::unique_ptr<message> parse_ready_message(rapidjson::Document const& doc) const;
		std::unique_ptr<message> parse_death_message(rapidjson::Document const& doc) const;
		std::unique_ptr<message> parse_spawned_message(rapidjson::Document const& doc) const;

		void build_message(respawn_message const& msg, json_writer& writer) const;
		void build_message(set_target_message const& msg, json_writer& writer) const;
	};
}

