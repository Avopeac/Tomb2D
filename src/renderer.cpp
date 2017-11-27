#include "renderer.h"
#include "core.h"

#include "post_effect.h"

using namespace graphics;

const std::string Renderer::render_target_name = "main_render_target";

Renderer::Renderer(GraphicsBase *graphics_base) :
	graphics_base_(graphics_base)
{
	render_target_ = CreateRenderTarget();
	sprite_renderer_ = std::make_unique<SpriteRenderer>(*graphics_base_);
	font_renderer_ = std::make_unique<FontRenderer>(*graphics_base_);
	post_processing_ = std::make_unique<PostProcessing>(*graphics_base_);
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

	auto * orthographic_camera = graphics_base_->GetOrthographicCamera();
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
		graphics_base_->GetBackbufferWidth(), graphics_base_->GetBackbufferHeight(),
		0, descriptors, nullptr);

}
