#include "json_message_parser.hpp"

#include <iostream>

using namespace caio;

std::unique_ptr<message> json_message_parser::parse(
		std::string const& str) const
{
	rapidjson::Document doc;
	doc.Parse(str.c_str());

	// TODO: error handling

	message::type messageType = (message::type)doc["type"].GetInt();

	switch (messageType)
	{
	case message::type::ready:
		return parse_ready_message(doc);
	};

	return std::unique_ptr<message>(nullptr);
}

std::unique_ptr<message> json_message_parser::parse_ready_message(
		rapidjson::Document const& doc) const
{
	return std::make_unique<ready_message>();
}

std::string json_message_parser::build(message const& msg) const
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

	writer.StartObject();
	
	writer.String("type");
	writer.Int((int)msg.opcode());

	switch(msg.opcode())
	{
		case message::type::respawn:
			build_message(dynamic_cast<respawn_message const&>(msg), writer);
			break;
		default:
			break;
	}

	writer.EndObject();
	return buffer.GetString();
}

void json_message_parser::build_message(respawn_message const& msg,
		json_writer& writer) const
{
	return;
}

