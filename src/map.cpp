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
		m.tile_width = json["tile_width"].get<int>();
		m.tile_height = json["tile_height"].get<int>();
		m.orientation = json["orientation"].get<std::string>();
		//m.layers = ?
		//m.tilesets = ?
		m.background_color = json["backgroundcolor"].get<std::string>();
		m.render_order = json["renderorder"].get<std::string>();
		//m.properties = ?
		m.next_object_id = json["nextobjectid"].get<int>();

		maps_[path] = m;

	}
	else
	{
		debug::Log(SDL_LOG_PRIORITY_ERROR, SDL_LOG_CATEGORY_INPUT, "Failed to load map.");
	}
}
