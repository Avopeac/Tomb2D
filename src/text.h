#pragma once

#include <string>

#include <unordered_map>

namespace core
{
	class TextCache
	{

		std::unordered_map<size_t, std::string> strings_;

	public:

		TextCache();

		~TextCache();

		const std::string * const GetTextFromFile(const std::string &path, size_t * hash = nullptr);
		
		const std::string * const GetTextFromHash(size_t hash);

	};

}
