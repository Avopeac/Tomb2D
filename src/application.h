#pragma once

#include "application_system_server.h"

namespace core {

	class Application
	{

	public:

		virtual ~Application() = default;

		virtual bool StartUp(const ApplicationSystemServer &, const Config &) = 0;

		virtual bool Run(const ApplicationSystemServer &, const Config &, float) = 0;

		virtual bool CleanUp(const ApplicationSystemServer &) = 0;

	protected:

		Application() = default;

	};
}
