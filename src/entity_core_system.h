#pragma once

#include "abstract_core_system.h"

namespace core {
	
	class EntityCoreSystem : public AbstractCoreSystem
	{
	public:

		EntityCoreSystem();

		~EntityCoreSystem();

		void StartUp(const Config &config) override;

		void CleanUp() override;
	};
}
