#pragma once

#include "abstract_core_system.h"

namespace core {

	class GuiCoreSystem : public AbstractCoreSystem
	{
	public:

		GuiCoreSystem();

		~GuiCoreSystem();

		void StartUp(const Config &config) override;

		void Update(float delta_time) override;

		void CleanUp() override;
	};
}
