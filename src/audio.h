#pragma once

#include "AL/al.h"
#include "AL/alc.h"

#include "config.h"

namespace audio {

	class AudioBase
	{

		ALCdevice * device_ = nullptr;

		std::string device_name_;

	public:

		AudioBase(const input::Config &config);

		~AudioBase();

	};
}
