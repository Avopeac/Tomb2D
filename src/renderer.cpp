#include "renderer.h"

#include "post_effect.h"

using namespace core;

const std::string Renderer::render_target_name = "main_render_target";

Renderer::Renderer(ResourceCoreSystem &resource_core, GraphicsCoreSystem &graphics_core) :
	resource_core_(resource_core), graphics_core_(graphics_core)
{
	render_target_ = CreateRenderTarget();
	sprite_renderer_ = std::make_unique<SpriteRenderer>(resource_core_, graphics_core_);
	font_renderer_ = std::make_unique<FontRenderer>(quad_, resource_core_, graphics_core_);
	post_processing_ = std::make_unique<PostProcessing>(quad_, resource_core_, graphics_core_);
	post_processing_->Add(std::move(std::make_unique<PostEffect>()));  

	glEnable(GL_CULL_FACE);
	glDisable(GL_MULTISAMPLE); 
	glCullFace(GL_BACK); 
}

Renderer::~Renderer()
{
}

void Renderer::Invoke(float frame_time)
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	graphics_core_.GetOrthographicCamera()->Update(frame_time);

	sprite_renderer_->Draw(frame_time);
	font_renderer_->Draw(frame_time);

	glDisable(GL_BLEND);

	post_processing_->Process();
}

core::FrameBuffer * Renderer::CreateRenderTarget()
{
	std::vector<core::FrameBufferAttachmentDescriptor> descriptors;

	core::FrameBufferAttachmentDescriptor composition;
	composition.format = GL_RGBA;
	composition.internal_format = GL_RGBA16F;
	composition.type = GL_FLOAT;

	descriptors.push_back(composition); 

	auto &frame_buffer_cache = resource_core_.GetFrameBufferCache();
	return frame_buffer_cache.GetFromParameters(render_target_name,
		graphics_core_.GetBackbufferWidth(), graphics_core_.GetBackbufferHeight(),
		0, descriptors, nullptr);

}
