#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <chrono>
#include <iomanip>
#include <iostream>

#undef ERROR


namespace caio
{
	enum error_level
	{
		debug = 1, info, warning, error, fatal
	};

	class logger
	{
	public:
		static logger& get(std::string const& name);

		void set_logging_level(error_level level);

		std::ostream& log(error_level level) const;
		std::ostream& debug() const;
		std::ostream& info() const;
		std::ostream& warning() const;
		std::ostream& error() const;
		std::ostream& fatal() const;

		std::string const& get_name() const;

		static void set_thread_name(std::string const& name);
		static void set_global_logging_level(error_level level);

	private:
		logger(std::string const& name);

		std::ostream& get_stream(error_level level) const;
		void print_tag(error_level level, std::ostream& stream) const;
		static std::string get_error_level_string(error_level level);
		std::string get_time_stamp() const;

		std::string m_name;
		error_level m_filter;

		static logger& create_logger(std::string const& name);

		static std::unordered_map<std::string, std::unique_ptr<logger>> loggers;
		static error_level global_filter;

		class dummy_stream_t : public std::basic_ostream<char>
		{

		};

		static dummy_stream_t dummy_stream;
		static std::ostream &out_stream, &error_stream, &debug_stream;
	};
}
