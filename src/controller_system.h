#pragma once

#include "system.h"

#include "sprite_component.h"
#include "controller_component.h"

namespace entity
{

	class ControllerSystem : public System<ControllerSystem, ControllerComponent, SpriteComponent>
	{

	public:

		ControllerSystem() {}

		virtual ~ControllerSystem() {}

		// Inherited via System
		virtual void Initialize(Entity * entity) override;

		virtual void Update(Entity * entity, float delta_time) override;

		virtual void Clean(Entity * entity) override;

	};
}
