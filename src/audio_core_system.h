#pragma once

#include <string>
#include <memory>
#include <queue>
#include <AL/al.h>
#include <AL/alc.h>
#include <glm/glm.hpp>

#include "abstract_core_system.h"
#include "audio_source.h"

namespace core {

	constexpr size_t MAX_AUDIO_SOURCES{ 128 };

	class AudioCoreSystem : public AbstractCoreSystem
	{

		ALCdevice * device_ = nullptr;
		ALCcontext * context_ = nullptr;

		std::string device_name_;

		glm::vec3 position_;
		glm::vec3 velocity_;
		glm::vec3 forward_;
		glm::vec3 up_;

		size_t audio_source_unique_id_counter_;
		std::queue<size_t> free_audio_source_unique_ids_;
		std::unordered_map<size_t, std::unique_ptr<AudioSource>> audio_sources_;
		
	public:

		AudioCoreSystem();

		~AudioCoreSystem();

		void StartUp(const Config &config) override;

		void Update(float delta_time) override;

		void CleanUp() override;

		void SetListenerPosition(const glm::vec3 &position);

		void SetListenerVelocity(const glm::vec3 &velocity);

		void SetListenerOrientation(const glm::vec3 &forward, const glm::vec3 &up);

		AudioSource * CreateAudioSource(const Sound * const sound);

		void DeleteAudioSource(size_t id);
	};
}
