#pragma once


#include "system.h"
#include "resource_core_system.h"
#include "sprite_component.h"
#include "sprite_animation_component.h"

namespace game
{

	class SpriteRenderSystem : public core::System<SpriteRenderSystem, SpriteComponent>
	{

		core::ResourceCoreSystem &resource_core_;

	public:

		SpriteRenderSystem(core::ResourceCoreSystem &resource_core);

		virtual ~SpriteRenderSystem();

		// Inherited via System
		virtual void Initialize(core::Entity * entity) override;

		virtual void Update(core::Entity * entity, float delta_time) override;

		virtual void Clean(core::Entity * entity) override;

	private:

		void InitializeSpriteComponent(SpriteComponent * sprite_component);

		void InitializeSpriteAnimationComponent(SpriteAnimationComponent * sprite_animation_component);

	};
}
