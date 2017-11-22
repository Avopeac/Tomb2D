#include "sound.h"

#include "SDL_audio.h"

using namespace graphics;

SoundCache::SoundCache()
{
}

SoundCache::~SoundCache()
{
	for (auto it = sound_data_.begin(); it != sound_data_.end(); ++it)
	{
		it->second.Free();
	}

	sound_data_.clear();


	for (auto it = sounds_.begin(); it != sounds_.end(); ++it)
	{
		it->second.Free();
	}

	sounds_.clear();
}

Sound * SoundCache::GetBufferFromFile(const std::string & path, size_t * hash = nullptr)
{

	size_t path_hash = std::hash<std::string>{}(path);

	Sound * sound = nullptr;

	if (sound_data_.find(path_hash) != sound_data_.end())
	{
		sound = &sounds_[path_hash];
	}

	SDL_AudioSpec spec;
	Uint8 * buffer;
	Uint32 length;
	SDL_LoadWAV(path.c_str(), &spec, &buffer, &length);

	SoundData data(spec, buffer, length);
	sound_data_.insert({ path_hash, std::move(data) });

	Sound new_sound;
	new_sound.Create(sound_data_[path_hash]);
	
	sounds_.insert({ path_hash, std::move(new_sound) });

	if (hash)
	{
		*hash = path_hash;
	}

	return sound;
}

Sound * SoundCache::GetBufferFromHash(size_t hash)
{
	if (sounds_.find(hash) != sounds_.end())
	{
		return &sounds_[hash];
	}

	return nullptr;
}

SoundData::SoundData(const SDL_AudioSpec & spec, Uint8 * buffer, Uint32 length) :
	spec_(spec), buffer_(buffer), length_(length)
{
}

SoundData::~SoundData()
{
}

void SoundData::Free()
{
	if (buffer_)
	{
		SDL_FreeWAV(buffer_);
	}
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
}

void Sound::Free()
{
	alDeleteBuffers(1, &id_);
}
