#pragma once

#include "system.h"
#include "sprite_component.h"
#include "sprite_animation_component.h"
#include "application_system_server.h"

namespace game
{

	class SpriteRenderSystem : public core::System<SpriteRenderSystem, SpriteComponent>
	{
		const core::ApplicationSystemServer &application_system_server_;

	public:

		SpriteRenderSystem(const core::ApplicationSystemServer &application_system_server);

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
