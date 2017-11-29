#pragma once


#include "system.h"
#include "resource_core_system.h"
#include "sprite_component.h"
#include "sprite_animation_component.h"

namespace core
{

	class SpriteRenderSystem : public System<SpriteRenderSystem, SpriteComponent>
	{

		ResourceCoreSystem &resource_core_;

	public:

		SpriteRenderSystem(ResourceCoreSystem &resource_core);

		virtual ~SpriteRenderSystem();

		// Inherited via System
		virtual void Initialize(Entity * entity) override;

		virtual void Update(Entity * entity, float delta_time) override;

		virtual void Clean(Entity * entity) override;

	private:

		void InitializeSpriteComponent(SpriteComponent * sprite_component);


		void InitializeSpriteAnimationComponent(SpriteAnimationComponent * sprite_animation_component);

	};
}
