#pragma once

#include "system.h"
#include "sprite_component.h"
#include "controller_component.h"
#include "input_core_system.h"

namespace core
{

	class ControllerSystem : public System<ControllerSystem, ControllerComponent, SpriteComponent>
	{

		InputCoreSystem &input_core_;

	public:

		ControllerSystem(InputCoreSystem &input_core);

		virtual ~ControllerSystem();

		// Inherited via System
		virtual void Initialize(Entity * entity) override;

		virtual void Update(Entity * entity, float delta_time) override;

		virtual void Clean(Entity * entity) override;

	};
}
