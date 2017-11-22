#pragma once

#include <unordered_map>

#include "AL/al.h"

#include "disposable.h"

namespace graphics {

	class SoundData : public base::Disposable
	{
		SDL_AudioSpec spec_;
		Uint32 length_;
		Uint8 * buffer_;

	public:

		SoundData(const SDL_AudioSpec &spec, 
			Uint8 * buffer = nullptr,
			Uint32 length = 0);

		~SoundData();

		inline const SDL_AudioSpec &GetSpec() const { return spec_; }

		inline Uint32 GetLength() const { return length_; }

		inline const Uint8 * const GetBuffer() const { return buffer_; }

		void Free() override;
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
