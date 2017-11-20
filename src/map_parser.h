#pragma once

#include <map>

#include <vector>

#include <unordered_map>

#include "map_data.h"

namespace game {

	class MapParser
	{

		std::unordered_map<std::string, MapData> maps_;

	public:

		MapParser();

		~MapParser();

		MapData &GetMapData(const std::string &path);

	};

}
