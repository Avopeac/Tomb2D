#include "post_processing.h"

#include "renderer.h"

#include "quad.h"

using namespace core;

PostProcessing::PostProcessing()
{
} 

PostProcessing::~PostProcessing()
{
}

void PostProcessing::Add(std::unique_ptr<PostProcessEffect> effect)
{
	effects_.push_back(std::move(effect));
	effects_.back()->Init();
}

void PostProcessing::Process()
{
	for (auto &effect : effects_)
	{
		effect->Apply();
	}
}

void PostProcessEffect::Render()
{	
	Quad::Get().Begin();
	Quad::Get().DrawElements();
	Quad::Get().End();
}
