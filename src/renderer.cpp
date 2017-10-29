#include "renderer.h"
#include "resource_manager.h"

#include "post_effect.h"

using namespace graphics;

const std::string Renderer::render_target_name = "main_render_target";

Renderer::Renderer(GraphicsBase *graphics_base) :
	graphics_base_(graphics_base)
{
	render_target_ = CreateRenderTarget();
	sprite_renderer_ = std::make_unique<SpriteRenderer>(*graphics_base_);
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

	auto * main_camera = graphics_base_->GetMainCamera();
	main_camera->Update(frame_time);
	sprite_renderer_->Draw(frame_time);
	post_processing_->Process();
}

FrameBuffer * Renderer::CreateRenderTarget()
{
	std::vector<FrameBufferAttachmentDescriptor> descriptors;

	FrameBufferAttachmentDescriptor composition;
	composition.format = GL_RGB;
	composition.internal_format = GL_RGB16F;
	composition.type = GL_FLOAT;

	descriptors.push_back(composition);

	auto &frame_buffer_cache = ResourceManager::Get().GetFrameBufferCache();
	return frame_buffer_cache.GetFromParameters(render_target_name,
		graphics_base_->GetBackbufferWidth(), graphics_base_->GetBackbufferHeight(),
		0, descriptors, nullptr);

}
