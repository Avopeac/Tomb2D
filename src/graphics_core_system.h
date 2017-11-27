#pragma once

#include "abstract_core_system.h"

namespace core {

	class GraphicsCoreSystem : AbstractCoreSystem
	{
	public:

		GraphicsCoreSystem(); 

		~GraphicsCoreSystem();

		void StartUp() override;

		void CleanUp() override;
	};
}
