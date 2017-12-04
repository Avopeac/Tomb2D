#pragma once

#include "system.h"
#include "sprite_component.h"
#include "controller_component.h"
#include "application_system_server.h"

namespace game
{

	class ControllerSystem : public core::System<ControllerSystem, ControllerComponent, SpriteComponent>
	{

		const core::ApplicationSystemServer &application_system_server_;

	public:

		ControllerSystem(const core::ApplicationSystemServer &application_system_server);

		virtual ~ControllerSystem();

		// Inherited via System
		virtual void Initialize(core::Entity * entity) override;

		virtual void Update(core::Entity * entity, float delta_time) override;

		virtual void Clean(core::Entity * entity) override;

	};
}
