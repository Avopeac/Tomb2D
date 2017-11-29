#pragma once

#include "system.h"
#include "sprite_component.h"
#include "controller_component.h"
#include "input_core_system.h"

namespace game
{

	class ControllerSystem : public core::System<ControllerSystem, ControllerComponent, SpriteComponent>
	{

		core::InputCoreSystem &input_core_;

	public:

		ControllerSystem(core::InputCoreSystem &input_core);

		virtual ~ControllerSystem();

		// Inherited via System
		virtual void Initialize(core::Entity * entity) override;

		virtual void Update(core::Entity * entity, float delta_time) override;

		virtual void Clean(core::Entity * entity) override;

	};
}
