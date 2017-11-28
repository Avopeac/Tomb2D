#include "map_view.h"

#include "glm/glm.hpp"

#include "glm/gtx/transform.hpp"

#include "core.h"

#include "entity_manager.h"

#include "sprite_component.h"

#include "sprite_renderer.h"

using namespace game;

MapView::MapView(MapData & map) : map_(map)
{
}

MapView::~MapView()
{
}

void MapView::Initialize()
{

	size_t pos = map_.path.find_last_of('/');
	std::string map_folder = map_.path.substr(0, pos + 1);

	glm::vec2 size_translate = core::Core::GetGraphicsSystem()->PixelsToScale(glm::uvec2(map_.tile_width, map_.tile_height));
	
	for (size_t i = 0; i < map_.layers.size(); ++i)
	{
		auto &layer = map_.layers[i];

		auto &data = layer.data;

		for (int y = 0; y < layer.height; ++y)
		{
			for (int x = 0; x < layer.width; ++x)
			{
				size_t data_index = x + y * layer.width;

				// TODO: Only one tileset supported
				if (data[data_index] == 0)
					continue;


				MapTileData tile_data = map_.tilesets[0].tiles[data[data_index] - 1];

				std::string rel_texture_path = tile_data.image;
				if (!rel_texture_path.empty())
				{
					const auto * tile = core::EntityManager::Get().CreateEntity("layer_" + std::to_string(i) +
						"_tile_" + std::to_string(data_index));

					std::string texture_path = map_folder + rel_texture_path;
					glm::mat4 transform = glm::scale(glm::vec3(core::Core::GetGraphicsSystem()->PixelsToScale(glm::uvec2(tile_data.image_width, tile_data.image_height)), 1.0f));
					transform[3] = glm::vec4((x - y) * size_translate.x,
						-(x + y) * size_translate.y, 0.0f, 1.0f);

					auto * sprite = core::EntityManager::Get().AddEntityComponent<core::SpriteComponent>(tile->id,
						texture_path,
						glm::vec4(1.0f),
						transform);

					sprite->SetLayer(map_.layers.size() - i);
				}
			}
		}
	}
}

void MapView::Update(float delta_time)
{
}
