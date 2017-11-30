#pragma once

#include "application_types.h"

namespace core {

	class Application
	{

	public:

		virtual ~Application() = default;

		virtual bool Run(const SystemsMap &, const Config &, float) = 0;

		virtual bool StartUp(const SystemsMap &, const Config &) = 0;

	protected:

		Application() = default;

	};
}
