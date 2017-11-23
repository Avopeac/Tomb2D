#pragma once

#include <unordered_map>

#include "AL/al.h"

#include "SDL_audio.h"

#include "disposable.h"

namespace graphics {

	struct SoundData
	{
		SDL_AudioSpec spec;
		Uint32 length = 0;
		Uint8 * buffer = nullptr;
	};

	class Sound : public base::Disposable
	{
		ALuint id_;

	public:

		Sound();

		~Sound();

		inline ALuint GetId() const { return id_; }

		void Create(const SoundData &sound_data);

		void Free() override;
	};

	class SoundCache
	{
		std::unordered_map<size_t, SoundData> sound_data_;

		std::unordered_map<size_t, Sound> sounds_;

	public:

		SoundCache();

		~SoundCache();

		Sound * GetBufferFromFile(const std::string &path, size_t * hash = nullptr);

		Sound * GetBufferFromHash(size_t hash);

	};

}
