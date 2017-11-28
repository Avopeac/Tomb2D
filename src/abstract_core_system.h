#pragma once

#include "config.h"

namespace core {

	class AbstractCoreSystem
	{
	public:

		AbstractCoreSystem() = default;

		~AbstractCoreSystem() = default;

		virtual void StartUp(const Config &config) = 0; 

		virtual void CleanUp() = 0;
	};
}