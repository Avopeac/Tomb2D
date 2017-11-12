#include "map.h"

#include "glm/glm.hpp"

#include "glm/gtx/transform.hpp"

#include "sprite_component.h"

#include "sprite_renderer.h"

using namespace game;

Map::Map()
{
}

Map::~Map()
{
}

void Map::Create()
{

	using namespace entity;
	glm::vec2 size = 0.2f * glm::vec2(1.0f, 2.0f); 

	for (int y = 0; y <= 20; ++y)
	{ 
		for (int x = 0; x <= 20; ++x)
		{
			glm::vec3 center;
			center.x = 1.0f * size.x * (x - y);
			center.y = 0.29296875f * size.y * (x + y); // = 0.5f * 150px / 256px, which was the tile size set by the assets
			center.z = 0.0;

			auto * e = EntityManager::Get().CreateEntity("tile0" + std::to_string(x) + "_" + std::to_string(y));
			auto * s = EntityManager::Get().AddEntityComponent<SpriteComponent>(e->id, "assets/textures/temp/dirt_W.png",
				glm::vec4(1.0f),
				glm::translate(center) * glm::scale(glm::vec3(size, 1.0)));
			s->SetMinFilter(graphics::MinificationFiltering::LinearMipmapLinear);
			s->SetMagFilter(graphics::MagnificationFiltering::Linear);
			s->SetShape(graphics::SpriteShape::Quad);
			s->SetLayer(graphics::MAX_SPRITE_LAYERS - 1);
		}
	}


	for (int y = 0; y <= 20; ++y)
	{
		for (int x = 0; x <= 20; ++x)
		{
			if (y == 0 || y == 20 || x == 0 || x == 20)
			{
				glm::vec3 center;
				center.x = 1.0f * size.x * (x - y);
				center.y = 0.29f * size.y * (x + y);
				center.z = 0.0;

				auto * e = EntityManager::Get().CreateEntity("tile1" + std::to_string(x) + "_" + std::to_string(y));
				auto * s = EntityManager::Get().AddEntityComponent<SpriteComponent>(e->id, "assets/textures/temp/dirtTiles_W.png",
					glm::vec4(1.0f),
					glm::translate(center) * glm::scale(glm::vec3(size, 1.0)));
				s->SetMinFilter(graphics::MinificationFiltering::LinearMipmapLinear);
				s->SetMagFilter(graphics::MagnificationFiltering::Linear);
				s->SetShape(graphics::SpriteShape::Quad);
				s->SetLayer(graphics::MAX_SPRITE_LAYERS - 2);
			}
		}
	}


}
