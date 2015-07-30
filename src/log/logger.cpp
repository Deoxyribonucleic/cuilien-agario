#include "logger.hpp"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <vector>
#include <ctime>

#ifdef __linux__
#include <pthread.h>
#endif


using namespace caio;

std::unordered_map<std::string, std::unique_ptr<logger>> logger::loggers;
error_level logger::global_filter = error_level::info;

logger::dummy_stream_t logger::dummy_stream;
std::ostream& logger::out_stream = std::cout;
std::ostream& logger::error_stream = std::cerr;

#ifdef DISABLE_DEBUG_LOGGING
std::ostream& logger::debugStream = logger::dummyStream;
#else
std::ostream& logger::debug_stream = std::cout;
#endif

logger::logger(std::string const& p_name)
	: m_name(p_name), m_filter(logger::global_filter)
{
}

std::ostream& logger::info() const
{
	return this->log(error_level::info);
}
std::ostream& logger::warning() const
{
	return this->log(error_level::warning);
}
std::ostream& logger::error() const
{
	return this->log(error_level::error);
}
std::ostream& logger::fatal() const
{
	return this->log(error_level::fatal);
}

std::ostream& logger::log(error_level p_level) const
{
	if(p_level < m_filter)
		return logger::dummy_stream;

	std::ostream& stream = this->get_stream(p_level);

	this->print_tag(p_level, stream);
	return stream;
}

std::ostream& logger::debug() const
{
	return this->log(error_level::debug);
}

std::ostream& logger::get_stream(error_level p_level) const
{
	switch(p_level)
	{
	case error_level::error:
	case error_level::fatal:
		return logger::error_stream;
	case error_level::debug:
		return logger::debug_stream;
	case error_level::warning:
	default:
		return logger::out_stream;
	}
}

void logger::print_tag(error_level p_level, std::ostream& p_stream) const
{
#ifdef __linux__
	// If we're on linux we can include pthread names in the output

	char buffer[32];
	pthread_getname_np(pthread_self(), buffer, 32);

	p_stream << this->get_time_stamp() << " " << buffer << " [" << logger::get_error_level_string(p_level) << "/" << m_name << "] ";
#else
	p_stream << this->getTimeStamp() << " [" << logger::geterror_levelString(p_level) << "/" << m_name << "] ";
#endif
}

std::string logger::get_time_stamp() const
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	auto localTimeData = localtime(&now);

	char str[32];
	sprintf(str, "%02d:%02d:%02d", localTimeData->tm_hour, localTimeData->tm_min, localTimeData->tm_sec);

	return std::string(str);
}

std::string logger::get_error_level_string(error_level p_level)
{
	switch(p_level)
	{
	case error_level::warning:
		return "WARNING";
	case error_level::error:
		return "ERROR";
	case error_level::fatal:
		return "FATAL";
	case error_level::debug:
		return "DEBUG";
	default:
		return "INFO";
	}
}

std::string const& logger::get_name() const
{
	return this->m_name;
}

logger& logger::get(std::string const& p_name)
{
	if(logger::loggers.find(p_name) == logger::loggers.end())
	{
		return logger::create_logger(p_name);
	}
	else
	{
		return *logger::loggers[p_name];
	}
}

void logger::set_logging_level(error_level level)
{
	m_filter = level;
}

logger& logger::create_logger(std::string const& name)
{
	logger* new_logger = new logger(name);
	logger::loggers[name].reset(new_logger);
	return *new_logger;
}

void logger::set_thread_name(std::string const& name)
{
	pthread_setname_np(pthread_self(), name.c_str());
}

void logger::set_global_logging_level(error_level level)
{
	logger::global_filter = level;
}

