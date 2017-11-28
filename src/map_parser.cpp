#include "map_parser.h"

#include <fstream>

#include "json/json.hpp"

#include "logger.h"

using namespace game;

MapParser::MapParser()
{
}

MapParser::~MapParser()
{
}

MapData &MapParser::GetMapData(const std::string &path)
{
	if (maps_.find(path) != maps_.end())
	{
		return maps_[path];
	}

	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		nlohmann::json json;

		ifs >> json;

		MapData m;
		m.path = path;
		m.width = json["width"].get<int>();
		m.height = json["height"].get<int>();
		m.tile_width = json["tilewidth"].get<int>();
		m.tile_height = json["tileheight"].get<int>();

		for (auto &layer_it = json["layers"].begin(); layer_it != json["layers"].end(); ++layer_it)
		{
			auto & json_layer = layer_it.value();

			MapLayerData layer{};
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

			MapTilesetData tileset{};
			tileset.columns = json_tilesets["columns"].get<int>();
			tileset.first_gid = json_tilesets["firstgid"].get<int>();
			tileset.margin = json_tilesets["margin"].get<int>();
			tileset.name = json_tilesets["name"].get<std::string>();
			tileset.spacing = json_tilesets["spacing"].get<int>();
			tileset.tile_count = json_tilesets["tilecount"].get<int>();
			tileset.tile_width = json_tilesets["tilewidth"].get<int>();
			tileset.tile_height = json_tilesets["tileheight"].get<int>();

			for (auto &tile_it = json_tilesets["tiles"].begin(); tile_it != json_tilesets["tiles"].end(); ++tile_it)
			{
				auto & json_tile = tile_it.value();

				MapTileData tile{};
				tile.image = json_tile["image"].get<std::string>();
				tile.image_width = json_tile["imagewidth"].get<int>();
				tile.image_height = json_tile["imageheight"].get<int>();
				tileset.tiles.insert({ std::atoi(tile_it.key().c_str()), tile});
			}

			m.tilesets.push_back(tileset);
		}
		
		maps_[path] = m;

	}
	else
	{
		core::Log(SDL_LOG_PRIORITY_ERROR, SDL_LOG_CATEGORY_INPUT, "Failed to load map.");
	}

	return maps_[path];
}
