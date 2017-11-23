#pragma once

#include "AL/al.h"
#include "AL/alc.h"

#include "glm/glm.hpp"

#include "config.h"

namespace audio {

	class AudioBase
	{

		ALCdevice * device_ = nullptr;

		ALCcontext * context_ = nullptr;

		std::string device_name_;

		glm::vec3 position_;

		glm::vec3 velocity_;

		glm::vec3 forward_;

		glm::vec3 up_;

	public:

		AudioBase(const input::Config &config);

		~AudioBase();

		void SetListenerPosition(const glm::vec3 &position);

		void SetListenerVelocity(const glm::vec3 &velocity);

		void SetListenerOrientation(const glm::vec3 &forward, const glm::vec3 &up);

	};
}
