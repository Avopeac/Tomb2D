#include "text.h"

#include <fstream>

#include <sstream>

#include <functional>

#include "logger.h"

using namespace core;

TextCache::TextCache()
{
}

TextCache::~TextCache()
{
}

const std::string * const TextCache::GetTextFromFile(const std::string & path, size_t * hash)
{

	size_t path_hash = std::hash<std::string>{}(path);
	if (strings_.find(path_hash) != strings_.end())
	{
		if (hash)
		{
			*hash = path_hash;
		}

		return &strings_[path_hash];
	}

	std::ostringstream output_stream;

	std::ifstream input_stream(path, std::ifstream::in);

	if (!input_stream.is_open())
	{
		Log(SDL_LOG_PRIORITY_ERROR, SDL_LOG_CATEGORY_INPUT, "Failed to open file.");
		SDL_assert(false);
	}

	output_stream << input_stream.rdbuf();

	strings_.insert({ path_hash, std::move(output_stream.str()) });

	return &strings_[path_hash];
}
