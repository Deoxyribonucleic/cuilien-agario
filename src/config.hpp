#pragma once

#include <string>
#include <memory>

#include <rapidjson/document.h>

#include "log/logger.hpp"

namespace caio 
{
	class config 
	{
		public:
			config();
			virtual ~config();

			bool load_config(std::string const& filename);

			// Trying to grab a value that doesn't exist will
			// return a "default" value for that type and
			// print a warning in the log
			int getInt(std::string const& key);
			double getDouble(std::string const& key);
			std::string getString(std::string const& key);
			bool getBool(std::string const& key);

		private:
			bool check_key(std::string const& key);

			rapidjson::Document m_document;
			logger& m_logger;

	};
}
