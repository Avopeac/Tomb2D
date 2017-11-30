#include "resource_core_system.h"

using namespace core;

ResourceCoreSystem::ResourceCoreSystem()
{

}

ResourceCoreSystem::~ResourceCoreSystem()
{
}

void ResourceCoreSystem::StartUp(const Config &config)
{
	blend_cache_ = std::make_unique<BlendCache>();
	frame_buffer_cache_ = std::make_unique<FrameBufferCache>();
	sampler_cache_ = std::make_unique<SamplerCache>();
	text_cache_ = std::make_unique<TextCache>();
	program_cache_ = std::make_unique<ProgramCache>(text_cache_.get());
	texture_cache_ = std::make_unique<TextureCache>();
	font_cache_ = std::make_unique<FontCache>();
	sound_cache_ = std::make_unique<SoundCache>();
	
}

void ResourceCoreSystem::Update(float delta_time)
{
	// Nothing here
}

void ResourceCoreSystem::CleanUp()
{
	// Nothing here
}
