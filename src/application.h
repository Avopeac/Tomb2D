#pragma once

#include "application_types.h"

namespace core {

	class Application
	{

	public:

		virtual ~Application() = default;

		virtual bool StartUp(const SystemPtrs &, const Config &) = 0;

		virtual bool Run(const SystemPtrs &, const Config &, float) = 0;

		virtual bool CleanUp(const SystemPtrs &) = 0;

	protected:

		Application() = default;

	};
}
