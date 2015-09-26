#include "config.hpp"

#include <iostream>
#include <fstream>

using namespace caio;

config::config()
	:
	m_logger(logger::get("config"))
{
}

config::~config()
{

}

bool config::load_config(std::string const& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		m_logger.error() << "Failed to open config file: " << filename << std::endl;
		return false;
	}

	file.seekg(0, std::ios_base::end);
	int filesize = file.tellg();
	if (filesize == -1)
	{
		m_logger.error() << "Failed to read file size" << std::endl;
		return false;
	}

	file.seekg(0, std::ios_base::beg);

	char* buffer = new char[filesize + 1];
	file.read(buffer, filesize);
	buffer[filesize] = 0;

	m_document.Parse(buffer);

	delete[] buffer;
	return true;
}

int config::getInt(std::string const& key)
{
	if (!check_key(key))
		return 0;

	rapidjson::Value& value = m_document[key.c_str()];
	if (value.IsInt())
	{
		return value.GetInt();
	}
	else
	{
		m_logger.error() << "Type mismatch: key '" << key << "' is not an int" << std::endl;
		return 0;
	}
}

double config::getDouble(std::string const& key)
{
	if (!check_key(key))
		return 0;

	rapidjson::Value& value = m_document[key.c_str()];
	if (value.IsDouble())
	{
		return value.GetDouble();
	}
	else
	{
		m_logger.error() << "Type mismatch: key '" << key << "' is not a double" << std::endl;
		return 0;
	}
}

std::string config::getString(std::string const& key)
{
	if (!check_key(key))
		return "";

	rapidjson::Value& value = m_document[key.c_str()];
	if (value.IsString())
	{
		return value.GetString();
	}
	else
	{
		m_logger.error() << "Type mismatch: key '" << key << "' is not a string" << std::endl;
		return "";
	}
}

bool config::getBool(std::string const& key)
{
	if (!check_key(key))
		return false;

	rapidjson::Value& value = m_document[key.c_str()];
	if (value.IsBool())
	{
		return value.GetBool();
	}
	else
	{
		m_logger.error() << "Type mismatch: key '" << key << "' is not a bool" << std::endl;
		return false;
	}
}

bool config::check_key(std::string const& key)
{
	if (!m_document.HasMember(key.c_str()))
	{
		m_logger.warning() << "Key '" << key << "' doesn't exist" << std::endl;
		return false;
	}
	return true;
}
