#pragma once

#include "engine_message.h"

namespace engine {

	class AbstractEngineSystem
	{

	public:

		AbstractEngineSystem() = default;

		~AbstractEngineSystem() = default;

		virtual void HandleMessage(EngineMessage * const message) = 0;

		virtual void Update(float delta_time) = 0;
	};
}
