#pragma once

#include "entity_manager.h"

#include <map>

namespace game {

	struct Layer
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

	struct Tile
	{
		std::string image;
		int image_height;
		int image_width;
	};

	struct Grid
	{
		int height;
		int width;
		std::string orientation;
	};

	struct Tileset
	{
		std::string name;
		int first_gid;
		int tile_width;
		int tile_height;
		int margin;
		int spacing;
		int columns;
		int tile_count;
		Grid grid;
		std::map<std::string, Tile> tiles;
	};

	struct Map
	{
		size_t json_version;
		std::string tiled_version;
		int width;
		int height;
		int tile_width;
		int tile_height;
		std::string type;
		std::string orientation;
		std::vector<Layer> layers;
		std::vector<Tileset> tilesets;
		std::string background_color;
		std::string render_order;
		std::unordered_map<std::string, std::string> properties;
		int next_object_id;
	};

	class MapParser
	{

		std::unordered_map<std::string, Map> maps_;

	public:

		MapParser();

		~MapParser();

		void Load(const std::string &path);
	};

}
