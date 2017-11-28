#pragma once

#include "glm/glm.hpp"

#include "sound.h"

namespace core {

	class AudioSource
	{

		ALuint source_id_ = 0;

		glm::vec3 position_;

		glm::vec3 velocity_;

		glm::vec3 direction_;

	public:
		
		AudioSource(const core::Sound * sound);
		
		~AudioSource();

		void SetRepeating(bool repeating);

		void Play();

		void Pause();

		void Stop();

		void SetPosition(const glm::vec3 &position);

		void SetVelocity(const glm::vec3 &velocity);

		void SetDirection(const glm::vec3 &direction);

		void SetGain(float gain);
	};
}
