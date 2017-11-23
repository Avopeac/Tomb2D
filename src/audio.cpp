#include "audio.h"

#include "logger.h"

using namespace audio;

AudioBase::AudioBase(const input::Config & config) :
	position_(0), velocity_(0), forward_(0, 0, -1), up_(0, 1, 0)
{
	device_name_ = std::string(alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER));

	if (device_ = alcOpenDevice(device_name_.c_str()))
	{

		std::string message = "Loaded audio device with name ";
		message.append(device_name_);
		debug::Log(SDL_LOG_PRIORITY_INFO, SDL_LOG_CATEGORY_AUDIO, message.c_str());


		context_ = alcCreateContext(device_, nullptr);
		alcMakeContextCurrent(context_);
	}
	else
	{
		std::string message = "Failed to load audio device with name";
		message.append(device_name_);
		debug::Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_AUDIO, message.c_str());
	}

	// Clear error messages
	alGetError();
}

AudioBase::~AudioBase()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context_);
	alcCloseDevice(device_);
}

void AudioBase::SetListenerPosition(const glm::vec3 & position)
{
	alListener3f(AL_POSITION, position_.x, position_.y, position_.z);
}

void AudioBase::SetListenerVelocity(const glm::vec3 & velocity)
{
	alListener3f(AL_VELOCITY, velocity_.x, velocity_.y, velocity_.z);
}

void AudioBase::SetListenerOrientation(const glm::vec3 & forward, const glm::vec3 &up)
{

	forward_ = forward;

	up_ = up;

	float values[6]{ forward_.x, forward_.y, forward_.z, up_.x, up_.y, up_.z };

	alListenerfv(AL_ORIENTATION, &values[0]);
}
