#pragma once

#include <string>
#include <memory>

#include <rapidjson/document.h>

namespace caio 
{
	class config 
	{
		public:
			config();
			virtual ~config();

			bool load_config(std::string const& filename);

			// Also need default values
			int getInt(std::string const& key);
			float getFloat(std::string const& key);
			std::unique_ptr<std::string> getString(std::string const& key);
			bool getBool(std::string const& key);

		private:
			std::unique_ptr<rapidjson::Document> m_document;
	};
}
