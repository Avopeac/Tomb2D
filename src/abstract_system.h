#pragma once

#include "entity_types.h"

namespace core 
{
	class EntityCoreSystem;

	class AbstractSystem
	{
	public:

		virtual void TryInitialize(Entity * entity, EntityCoreSystem * manager) = 0;

		virtual void TryUpdate(Entity * entity, float delta_time) = 0;

		virtual void TryClean(Entity * entity) = 0;

		virtual ~AbstractSystem() {}

	protected:

		EntityCoreSystem * manager_;

		AbstractSystem() {}
	};
}