#include "sound.h"

#include "SDL_assert.h"

using namespace graphics;

SoundCache::SoundCache()
{
}

SoundCache::~SoundCache()
{
	for (auto it = sound_data_.begin(); it != sound_data_.end(); ++it)
	{
		if (it->second.buffer)
		{
			SDL_FreeWAV(it->second.buffer);
		}
	}

	sound_data_.clear();


	for (auto it = sounds_.begin(); it != sounds_.end(); ++it)
	{
		it->second.Free();
	}

	sounds_.clear();
}

Sound * SoundCache::GetBufferFromFile(const std::string & path, size_t * hash)
{

	size_t path_hash = std::hash<std::string>{}(path);

	if (sound_data_.find(path_hash) != sound_data_.end())
	{
		if (hash)
		{
			*hash = path_hash;
		}

		return &sounds_[path_hash];
	}

	
	SoundData data;
	SDL_LoadWAV(path.c_str(), &data.spec, &data.buffer, &data.length);
	sound_data_.insert({ path_hash, std::move(data) });

	Sound new_sound;
	new_sound.Create(sound_data_[path_hash]);
	sounds_.insert({ path_hash, std::move(new_sound) });

	if (hash)
	{
		*hash = path_hash;
	}

	return &sounds_[path_hash];
}

Sound * SoundCache::GetBufferFromHash(size_t hash)
{
	if (sounds_.find(hash) != sounds_.end())
	{
		return &sounds_[hash];
	}

	return nullptr;
}

Sound::Sound()
{
}

Sound::~Sound()
{
}

void Sound::Create(const SoundData & sound_data)
{
	alGenBuffers(1, &id_);

	ALenum format = 0;

	if (SDL_AUDIO_BITSIZE(sound_data.spec.format) == 16)
	{
		format = sound_data.spec.channels == 1 ?
			AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	}
	else if (SDL_AUDIO_BITSIZE(sound_data.spec.format) == 8)
	{
		format = sound_data.spec.channels == 1 ?
			AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
	}

	SDL_assert(format != 0);

	alBufferData(id_, format, sound_data.buffer,
		sound_data.length, sound_data.spec.freq);
}

void Sound::Free()
{
	alDeleteBuffers(1, &id_);
}
