#include "sampler.h"

#include "logger.h"

using namespace core;

Sampler::Sampler() :
	unit_(0), id_(0)
{
	glGenSamplers(1, &id_);
}

Sampler::~Sampler()
{
}

Sampler::Sampler(const Sampler &&other)
{
	id_ = other.id_;
	unit_ = other.unit_;
}

void Sampler::SetFiltering(MagnificationFiltering mag, MinificationFiltering min)
{
	glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(min));
	glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(mag));
}

void Sampler::SetWrap(Wrapping s, Wrapping t)
{
	glSamplerParameteri(id_, GL_TEXTURE_WRAP_S, static_cast<GLint>(s));
	glSamplerParameteri(id_, GL_TEXTURE_WRAP_T, static_cast<GLint>(t));
}

void Sampler::Bind(Uint32 unit)
{
	glBindSampler(unit, id_);
	unit_ = unit;
}

void Sampler::Unbind()
{
	glBindSampler(unit_, 0);
	unit_ = 0;
}

void Sampler::Free()
{
	glDeleteSamplers(1, &id_);
}

SamplerCache::SamplerCache()
{
}

SamplerCache::~SamplerCache()
{
	for (auto &sampler : samplers_)
	{
		sampler.second.Free();
	}
}

Sampler * SamplerCache::GetFromParameters(MagnificationFiltering mag,
	MinificationFiltering min, Wrapping s, Wrapping t, size_t * hash)
{
	size_t parameter_hash = static_cast<GLint>(mag) | static_cast<GLint>(min);
	parameter_hash ^= static_cast<GLint>(s) | static_cast<GLint>(t);

	if (samplers_.find(parameter_hash) == samplers_.end())
	{
		Sampler sampler;
		sampler.SetFiltering(mag, min);
		sampler.SetWrap(s, t);
		samplers_.insert({ parameter_hash, std::move(sampler) });
	}

	if (hash)
	{
		*hash = parameter_hash;
	}

	return &samplers_[parameter_hash];
}

Sampler * SamplerCache::GetFromHash(size_t hash)
{
	SDL_assert(samplers_.find(hash) != samplers_.end());
	if (samplers_.find(hash) != samplers_.end())
	{
		return &samplers_[hash];
	}

	Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_RENDER, "Sampler was null.");
	return nullptr;
}
