#include "post_processing.h"
#include "renderer.h"

using namespace core;

PostProcessing::PostProcessing(RenderQuad &quad, ResourceCoreSystem &resource_core, GraphicsCoreSystem &graphics_core) :
	quad_(quad), resource_core_(resource_core), graphics_core_(graphics_core)
{
} 

PostProcessing::~PostProcessing()
{
}

void PostProcessing::Add(std::unique_ptr<PostProcessEffect> effect)
{
	effects_.push_back(std::move(effect));
	effects_.back()->Init(resource_core_);
}

void PostProcessing::Process()
{
	for (auto &effect : effects_)
	{
		effect->Apply(quad_, resource_core_, graphics_core_);
	}
}
