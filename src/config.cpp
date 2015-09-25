#include "config.hpp"

#include <iostream>
#include <fstream>

using namespace caio;

config::config()
{

}

config::~config()
{

}

bool config::load_config(std::string const& filename)
{
	std::ifstream file;
	file.open(filename);
	return true;
}

// Also need default values
int config::getInt(std::string const& key)
{
	return 0;
}

float config::getFloat(std::string const& key)
{
	return 0;
}

std::unique_ptr<std::string> config::getString(std::string const& key)
{
	return std::move(std::make_unique<std::string>("test"));
}

bool config::getBool(std::string const& key)
{
	return false;
}
