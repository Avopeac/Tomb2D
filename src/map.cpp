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

	float size = 1.0f;

	for (int i = -2; i <= 2; ++i)
	{ 
		for (int j = -2; j <= 2; ++j)
		{
			glm::vec3 center;
			center.x = 2.0f * j - i;
			center.y = 0.5f * i;
			center.z = 0.0;

			auto * e = EntityManager::Get().CreateEntity("tile" + std::to_string(j) + "_" + std::to_string(i));
			auto * s = EntityManager::Get().AddEntityComponent<SpriteComponent>(e->id, "assets/textures/temp/sand.png",
				glm::vec4(1.0f),
				glm::translate(center) * glm::scale(glm::vec3(size, size, 1.0)));
			s->SetShape(graphics::SpriteShape::IsometricQuad);
			s->SetLayer(graphics::MAX_SPRITE_LAYERS - 1);
		}
	}
	

}
