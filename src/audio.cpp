#include "audio.h"

#include "logger.h"

using namespace audio;

AudioBase::AudioBase(const input::Config & config)
{
	device_name_ = std::string(alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER));

	if (device_ = alcOpenDevice(device_name_.c_str()))
	{
		
		std::string message = "Loaded audio device with name ";
		message.append(device_name_);
		debug::Log(SDL_LOG_PRIORITY_INFO, SDL_LOG_CATEGORY_AUDIO, message.c_str());
	}
	else
	{
		std::string message = "Failed to load audio device with name";
		message.append(device_name_);
		debug::Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_AUDIO, message.c_str());
	}
}

AudioBase::~AudioBase()
{
}
