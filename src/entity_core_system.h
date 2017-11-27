#pragma once

#include "abstract_core_system.h"

namespace core {
	
	class EntityCoreSystem : public AbstractCoreSystem
	{
	public:

		EntityCoreSystem();

		~EntityCoreSystem();

		void StartUp() override;

		void CleanUp() override;
	};
}
