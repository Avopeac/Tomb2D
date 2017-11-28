#include "resource_core_system.h"

using namespace core;

ResourceCoreSystem::ResourceCoreSystem()
{

}

ResourceCoreSystem::~ResourceCoreSystem()
{
}

void ResourceCoreSystem::StartUp()
{
	blend_cache_ = std::make_unique<BlendCache>();
	frame_buffer_cache_ = std::make_unique<FrameBufferCache>();
	sampler_cache_ = std::make_unique<SamplerCache>();
	program_cache_ = std::make_unique<ProgramCache>();
	texture_cache_ = std::make_unique<TextureCache>();
	font_cache_ = std::make_unique<FontCache>();
	sound_cache_ = std::make_unique<SoundCache>();
	text_cache_ = std::make_unique<TextCache>();
}

void ResourceCoreSystem::CleanUp()
{
	
}
