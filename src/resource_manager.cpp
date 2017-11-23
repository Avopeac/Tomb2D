#include "resource_manager.h"

using namespace graphics;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Initialize()
{
	blend_cache_ = std::make_unique<BlendCache>();
	frame_buffer_cache_ = std::make_unique<FrameBufferCache>();
	sampler_cache_ = std::make_unique<SamplerCache>();
	program_cache_ = std::make_unique<ProgramCache>();
	texture_cache_ = std::make_unique<TextureCache>();
	font_cache_ = std::make_unique<FontCache>();
	sound_cache_ = std::make_unique<SoundCache>();
}
