#pragma once

#include <vector>
#include <map>
#include <unordered_map>

namespace game {
	struct MapLayerData
	{
		int width;
		int height;
		std::string name;
		std::string type;
		bool visible;
		int x;
		int y;
		std::vector<int> data;
		float opacity;
	};

	struct MapTileData
	{
		std::string image;
		int image_height;
		int image_width;
	};

	struct MapTilesetData
	{
		std::string name;
		int first_gid;
		int tile_width;
		int tile_height;
		int margin;
		int spacing;
		int columns;
		int tile_count;
		std::map<int, MapTileData> tiles;
	};

	struct MapData
	{
		std::string path;
		int width;
		int height;
		int tile_width;
		int tile_height;
		std::vector<MapLayerData> layers;
		std::vector<MapTilesetData> tilesets;
	};
}
