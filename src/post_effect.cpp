#include "post_effect.h"

#include "renderer.h"

#include "sprite_renderer.h"

#include "timing.h"

using namespace graphics;

PostEffect::PostEffect()
{
}

PostEffect::~PostEffect()
{
} 

void PostEffect::Init()
{

	auto &program_cache = ResourceManager::Get().GetProgramCache();
	auto &frame_buffer_cache = ResourceManager::Get().GetFrameBufferCache();

	vertex_shader_ = program_cache.GetFromFile(v_name_, GL_VERTEX_SHADER, v_path_);
	fragment_shader_ = program_cache.GetFromFile(f_name_, GL_FRAGMENT_SHADER, f_path_);

	pipeline_.SetStages(*vertex_shader_);
	pipeline_.SetStages(*fragment_shader_);

	fbo0_ = frame_buffer_cache.GetFromName(Renderer::render_target_name);

	size_t num_attachments = fbo0_->GetColorAttachmentCount();

	for (int i = 0; i < (int)num_attachments; ++i)
	{
		fragment_shader_->SetUniform("u_texture" + std::to_string(i), (void*)&i);
	}
}

void PostEffect::Apply()
{
	
	fbo0_->UnbindDraw();

	size_t num_attachments = fbo0_->GetColorAttachmentCount();

	for (int i = 0; i < (int)num_attachments; ++i)
	{
		fbo0_->BindColorAttachment(i, i); 
	}

	auto &fbo_resource = ResourceManager::Get().GetFrameBufferCache();

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);   
	glDrawBuffer(GL_BACK); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
	 
	float time = (float)util::GetSeconds();
	 
	glm::vec2 texel_size{ graphics_base_->GetBackbufferWidth(), graphics_base_->GetBackbufferHeight() };
	texel_size = 1.0f / texel_size;

	fragment_shader_->SetUniform("u_texel_size", (void *)&texel_size);
	fragment_shader_->SetUniform("u_time", (void*)&time);

	pipeline_.Bind();  
	
	Render();   
	
	pipeline_.Unbind();    
	 
} 
