#pragma once

#include "entity_types.h"

namespace core 
{
	class EntityManager;

	class AbstractSystem
	{
	public:

		virtual void TryInitialize(Entity * entity, EntityManager * manager) = 0;

		virtual void TryUpdate(Entity * entity, float delta_time) = 0;

		virtual void TryClean(Entity * entity) = 0;

		virtual ~AbstractSystem() {}

	protected:

		EntityManager * manager_;

		AbstractSystem() {}
	};
}