#include "renderer.h"
#include "core.h"

#include "post_effect.h"

using namespace core;

const std::string Renderer::render_target_name = "main_render_target";

Renderer::Renderer()
{
	render_target_ = CreateRenderTarget();
	sprite_renderer_ = std::make_unique<SpriteRenderer>();
	font_renderer_ = std::make_unique<FontRenderer>();
	post_processing_ = std::make_unique<PostProcessing>();
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

	auto * orthographic_camera = Core::GetGraphicsSystem()->GetOrthographicCamera();
	orthographic_camera->Update(frame_time);

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

	auto &frame_buffer_cache = core::Core::GetResourceSystem()->GetFrameBufferCache();
	return frame_buffer_cache.GetFromParameters(render_target_name,
		Core::GetGraphicsSystem()->GetBackbufferWidth(), Core::GetGraphicsSystem()->GetBackbufferHeight(),
		0, descriptors, nullptr);

}
