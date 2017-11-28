#pragma once

#include <string>

#include "abstract_core_system.h"

#include "AL/al.h"

#include "AL/alc.h"

#include "glm/glm.hpp"

namespace core {

	class AudioCoreSystem : public AbstractCoreSystem
	{

		ALCdevice * device_ = nullptr;

		ALCcontext * context_ = nullptr;

		std::string device_name_;

		glm::vec3 position_;

		glm::vec3 velocity_;

		glm::vec3 forward_;

		glm::vec3 up_;

	public:

		AudioCoreSystem();

		~AudioCoreSystem();

		void StartUp(const Config &config) override;

		void CleanUp() override;

		void SetListenerPosition(const glm::vec3 &position);

		void SetListenerVelocity(const glm::vec3 &velocity);

		void SetListenerOrientation(const glm::vec3 &forward, const glm::vec3 &up);

	};
}
