#pragma once

#pragma once

#include "system.h"

#include "sprite_component.h"

namespace entity
{

	class SpriteRenderSystem : public System<SpriteRenderSystem, SpriteComponent>
	{

	public:

		SpriteRenderSystem() {}

		virtual ~SpriteRenderSystem() {}

		// Inherited via System
		virtual void Initialize(Entity * entity) override;

		virtual void Update(Entity * entity) override;

		virtual void Clean(Entity * entity) override;

	};
}
