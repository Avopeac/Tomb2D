#include "map_view.h"

#include "glm/glm.hpp"

#include "glm/gtx/transform.hpp"

#include "entity_manager.h"

#include "sprite_component.h"

#include "sprite_renderer.h"

using namespace game;

MapView::MapView(const graphics::GraphicsBase &graphics_base, MapData & map) :
	graphics_base_(graphics_base), map_(map)
{
}

MapView::~MapView()
{
}

void MapView::Initialize()
{

	size_t pos = map_.path.find_last_of('/');
	std::string map_folder = map_.path.substr(0, pos + 1);

	glm::vec2 size_aspect = graphics_base_.PixelsToScaleAspect(glm::uvec2(map_.tile_width, map_.tile_height));
	glm::vec2 size_translate = 0.5f * graphics_base_.PixelsToScale(glm::uvec2(map_.tile_width, map_.tile_height));
	
	for (size_t i = 0; i < 1 /*map_.layers.size()*/; ++i)
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

				std::string rel_texture_path = map_.tilesets[0].tiles[data[data_index] - 1].image;
				if (!rel_texture_path.empty())
				{
					const auto * tile = entity::EntityManager::Get().CreateEntity("layer_" + std::to_string(i) +
						"_tile_" + std::to_string(data_index));

					std::string texture_path = map_folder + rel_texture_path;
					glm::mat4 transform = glm::scale(glm::vec3(size_aspect, 1.0f));
					transform[3] = glm::vec4(x * size_aspect.x - 0.5f * (y * size_aspect.y), 
						-0.25f * y * size_aspect.y - 0.5f * x * size_aspect.x, 0.0f, 1.0f);

					auto * sprite = entity::EntityManager::Get().AddEntityComponent<entity::SpriteComponent>(tile->id,
						texture_path,
						glm::vec4(1.0f),
						transform);

					sprite->SetLayer(i);
				}
			}
		}
	}
}

void MapView::Update(float delta_time)
{
}
