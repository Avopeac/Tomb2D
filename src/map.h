#pragma once

#include "entity_manager.h"

namespace game {

	struct Point
	{
		float x, y;
	};

	struct Object
	{
		int id;
		int width;
		int height;
		std::string name;
		std::string type;
		std::unordered_map <std::string, std::string> properties;
		bool visible;
		int x;
		int y;
		float rotation;
		int gid;
		bool point;
		bool ellipse;
		std::vector<Point> polygon;
		std::vector<Point> polyline;
		std::unordered_map<std::string, std::string> text;
	};

	struct Layer
	{
		int width;
		int height;
		std::string name;
		std::string type;
		bool visible;
		int x;
		int y;
		int data;
		std::vector<Object> objects;
		std::unordered_map<std::string, std::string> properties;
		float opacity;
		std::string draw_order;
	};

	struct Terrain
	{
		std::string name;
		int tile;
	};

	struct Tiles
	{
		std::vector<int> terrain;
	};

	struct Tileset
	{
		int first_gid;
		std::string image;
		std::string name;
		int tile_width;
		int tile_height;
		int image_width;
		int image_height;
		std::unordered_map<std::string, std::string> properties;
		std::unordered_map<std::string, std::string> property_types;
		int margin;
		int spacing;
		std::unordered_map<std::string, std::string> tile_properties;
		std::vector<Terrain> terrains;
		int columns;
		int tile_count;
		std::unordered_map<int, Tiles> tiles;
	};

	struct Map
	{
		size_t json_version;
		std::string tiled_version;
		int width;
		int height;
		int tile_width;
		int tile_height;
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
