#include "map.h"

#include <fstream>

#include "json/json.hpp"

#include "glm/glm.hpp"

#include "glm/gtx/transform.hpp"

#include "sprite_component.h"

#include "sprite_renderer.h"

using namespace game;

MapParser::MapParser()
{
}

MapParser::~MapParser()
{
}

void MapParser::Load(const std::string &path)
{
	std::ifstream ifs(path);


	if (ifs.is_open())
	{
		nlohmann::json json;

		ifs >> json;

		Map m;
		
		m.json_version = json["version"].get<int>();
		m.tiled_version = json["tiledversion"].get<std::string>();
		m.width = json["width"].get<int>();
		m.height = json["height"].get<int>();
		m.tile_width = json["tilewidth"].get<int>();
		m.tile_height = json["tileheight"].get<int>();
		m.orientation = json["orientation"].get<std::string>();
		m.render_order = json["renderorder"].get<std::string>();
		m.next_object_id = json["nextobjectid"].get<int>();
		m.type = json["type"].get<std::string>();

		for (auto &layer_it = json["layers"].begin(); layer_it != json["layers"].end(); ++layer_it)
		{
			auto & json_layer = layer_it.value();

			Layer layer{};
			layer.height = json_layer["height"].get<int>();
			layer.name = json_layer["name"].get<std::string>();
			layer.opacity = json_layer["opacity"].get<float>();
			layer.type = json_layer["type"].get<std::string>();
			layer.visible = json_layer["visible"].get<bool>();
			layer.width = json_layer["width"].get<int>();
			layer.x = json_layer["x"].get<int>();
			layer.y = json_layer["y"].get<int>();
		
			for (auto &data_it = json_layer["data"].begin(); data_it != json_layer["data"].end(); ++data_it)
			{
				layer.data.push_back(data_it.value().get<int>());
			}

			m.layers.push_back(layer);
		}

		for (auto &tileset_it = json["tilesets"].begin(); tileset_it != json["tilesets"].end(); ++tileset_it)
		{
			auto & json_tilesets = tileset_it.value();

			Tileset tileset{};
			tileset.columns = json_tilesets["columns"].get<int>();
			tileset.first_gid = json_tilesets["firstgid"].get<int>();
			tileset.grid.height = json_tilesets["grid"]["height"].get<int>();
			tileset.grid.width = json_tilesets["grid"]["width"].get<int>();
			tileset.grid.orientation = json_tilesets["grid"]["orientation"].get<std::string>();
			tileset.margin = json_tilesets["margin"].get<int>();
			tileset.name = json_tilesets["name"].get<std::string>();
			tileset.spacing = json_tilesets["spacing"].get<int>();
			tileset.tile_count = json_tilesets["tilecount"].get<int>();
			tileset.tile_width = json_tilesets["tilewidth"].get<int>();
			tileset.tile_height = json_tilesets["tileheight"].get<int>();

			for (auto &tile_it = json_tilesets["tiles"].begin(); tile_it != json_tilesets["tiles"].end(); ++tile_it)
			{
				auto & json_tile = tile_it.value();
				
				Tile tile{};
				tile.image = json_tile["image"].get<std::string>();
				tile.image_width = json_tile["imagewidth"].get<int>();
				tile.image_height = json_tile["imageheight"].get<int>();
				tileset.tiles.insert({ tile_it.key(), tile});
			}

			m.tilesets.push_back(tileset);
		}
		
		maps_[path] = m;

	}
	else
	{
		debug::Log(SDL_LOG_PRIORITY_ERROR, SDL_LOG_CATEGORY_INPUT, "Failed to load map.");
	}
}
