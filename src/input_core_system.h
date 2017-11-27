#pragma once

#include "abstract_core_system.h"

namespace core {

	class InputCoreSystem : public AbstractCoreSystem
	{
	public:

		InputCoreSystem();

		~InputCoreSystem();

		void StartUp() override;

		void CleanUp() override;
	};

}
