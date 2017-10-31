#pragma once

#pragma once

#include "system.h"

#include "sprite_component.h"
#include "sprite_animation_component.h"

namespace entity
{

	class SpriteRenderSystem : public System<SpriteRenderSystem, SpriteComponent>
	{

	public:

		SpriteRenderSystem() {}

		virtual ~SpriteRenderSystem() {}

		// Inherited via System
		virtual void Initialize(Entity * entity) override;

		virtual void Update(Entity * entity, float delta_time) override;

		virtual void Clean(Entity * entity) override;

	private:

		void InitializeSpriteComponent(SpriteComponent * sprite_component);


		void InitializeSpriteAnimationComponent(SpriteAnimationComponent * sprite_animation_component);

	};
}
