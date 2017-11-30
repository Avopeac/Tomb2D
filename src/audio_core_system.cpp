#include "audio_core_system.h"

#include <string>

#include "logger.h"

using namespace core;

AudioCoreSystem::AudioCoreSystem() :
	position_(0), velocity_(0), forward_(0, 0, -1), up_(0, 1, 0),
	audio_source_unique_id_counter_(0)
{
}

AudioCoreSystem::~AudioCoreSystem()
{
}

void AudioCoreSystem::StartUp(const Config &config)
{
	device_name_ = std::string(alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER));

	if (device_ = alcOpenDevice(device_name_.c_str()))
	{

		std::string message = "Loaded audio device with name ";
		message.append(device_name_);
		Log(SDL_LOG_PRIORITY_INFO, SDL_LOG_CATEGORY_AUDIO, message.c_str());


		context_ = alcCreateContext(device_, nullptr);
		alcMakeContextCurrent(context_);
	}
	else
	{
		std::string message = "Failed to load audio device with name";
		message.append(device_name_);
		Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_AUDIO, message.c_str());
	}

	// Clear error messages
	alGetError();
}

void AudioCoreSystem::Update(float delta_time)
{
	// Nothing here
}

void AudioCoreSystem::CleanUp()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context_);
	alcCloseDevice(device_);
}

void AudioCoreSystem::SetListenerPosition(const glm::vec3 & position)
{
	alListener3f(AL_POSITION, position_.x, position_.y, position_.z);
}

void AudioCoreSystem::SetListenerVelocity(const glm::vec3 & velocity)
{
	alListener3f(AL_VELOCITY, velocity_.x, velocity_.y, velocity_.z);
}

void AudioCoreSystem::SetListenerOrientation(const glm::vec3 & forward, const glm::vec3 &up)
{

	forward_ = forward;

	up_ = up;

	float values[6]{ forward_.x, forward_.y, forward_.z, up_.x, up_.y, up_.z };

	alListenerfv(AL_ORIENTATION, &values[0]);
}

AudioSource * AudioCoreSystem::CreateAudioSource(const Sound * const sound)
{
	AudioSource * source = nullptr;

	if (audio_source_unique_id_counter_ < MAX_AUDIO_SOURCES ||
		!free_audio_source_unique_ids_.empty())
	{
		size_t unique_id;
		if (!free_audio_source_unique_ids_.empty())
		{
			unique_id = free_audio_source_unique_ids_.front();
			free_audio_source_unique_ids_.pop();
		}
		else
		{
			unique_id = audio_source_unique_id_counter_++;
		}

		auto source_ptr = std::make_unique<AudioSource>(sound, unique_id);
		source = source_ptr.get();

		audio_sources_.insert({ unique_id, std::move(source_ptr) });
	}
	else
	{
		SDL_assert(false && "Too many audio sources.");
	}

	return source;
}

void AudioCoreSystem::DeleteAudioSource(size_t id)
{
	if (audio_sources_.find(id) != audio_sources_.end())
	{
		size_t unique_id = audio_sources_[id]->GetUniqueId();
		free_audio_source_unique_ids_.push(unique_id);
		audio_sources_.erase(unique_id);
	}
}
