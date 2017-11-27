#pragma once

#include "abstract_core_system.h"

namespace core {

	class AudioCoreSystem : public AbstractCoreSystem
	{
	public:

		AudioCoreSystem();

		~AudioCoreSystem();

		void StartUp() override;

		void CleanUp() override;
	};
}
