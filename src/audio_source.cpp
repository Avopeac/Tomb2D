#include "audio_source.h"

using namespace audio;

AudioSource::AudioSource(const core::Sound * sound) :
	position_(0), velocity_(0), direction_(0)
{
	alGenSources(1, &source_id_);
	alSourcei(source_id_, AL_BUFFER, sound->GetId());
}

AudioSource::~AudioSource()
{
	alDeleteSources(1, &source_id_);
}

void AudioSource::SetRepeating(bool repeating)
{
	alSourcei(source_id_, AL_LOOPING, repeating ? 1 : 0);
}

void AudioSource::Play()
{
	alSourcePlay(source_id_);
}

void AudioSource::Pause()
{
	alSourcePause(source_id_);
}

void AudioSource::Stop()
{
	alSourceStop(source_id_);
}

void AudioSource::SetPosition(const glm::vec3 & position)
{
	position_ = position;

	alSource3f(source_id_, AL_POSITION, position_.x, position_.y, position_.z);
}

void AudioSource::SetVelocity(const glm::vec3 & velocity)
{
	velocity_ = velocity;

	alSource3f(source_id_, AL_VELOCITY, velocity_.x, velocity_.y, velocity_.z);
}

void AudioSource::SetDirection(const glm::vec3 & direction)
{
	direction_ = direction;

	alSource3f(source_id_, AL_DIRECTION, direction_.x, direction_.y, direction_.z);
}
