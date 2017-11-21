#include "font_renderer.h"

#include "glm/gtc/matrix_transform.hpp"

#include "data_pipe_hub.h"

#include "renderer.h"

#include "fullscreen_quad.h"

using namespace graphics;

FontRenderer::FontRenderer(const GraphicsBase & graphics_base) : 
	graphics_base_(graphics_base)
{
	default_vert_program_ = ResourceManager::Get().GetProgramCache().GetFromFile("default_font.vert", GL_VERTEX_SHADER, "assets/shaders/default_font.vert");
	default_frag_program_ = ResourceManager::Get().GetProgramCache().GetFromFile("default_font.frag", GL_FRAGMENT_SHADER, "assets/shaders/default_font.frag");

	pipeline_.SetStages(*default_vert_program_);
	pipeline_.SetStages(*default_frag_program_);

	size_t vertex_size = sizeof(float) * 2;
	size_t index_size = sizeof(Uint32);

	proj_ = glm::ortho(
		0.0f,
		(float)graphics_base_.GetBackbufferWidth(),
		0.0f,
		(float)graphics_base_.GetBackbufferHeight(),
		-1.0f, 1.0f);
}

FontRenderer::~FontRenderer()
{
}

void FontRenderer::Draw(float delta_time)
{
	FrameBuffer * render_target =
		ResourceManager::Get().GetFrameBufferCache().GetFromName(Renderer::render_target_name);

	render_target->BindDraw(0, 0, 0, 0, 0);

	FullscreenQuad::Get().Begin();

	pipeline_.Bind();

	auto &data = DataPipeHub::Get().GetTextDataPipe().GetData();
	for (auto it = data.begin(); it != data.end(); ++it)
	{
		auto * blend_mode = ResourceManager::Get().GetBlendCache().GetFromHash(it->blend_hash);
		auto * font = ResourceManager::Get().GetFontCache().GetFromHash(it->font_hash);
		auto * sampler = ResourceManager::Get().GetSamplerCache().GetFromHash(it->sampler_hash);

		glm::vec2 position = it->position;
		 
		int texture_index = 0; 
		for (size_t i = 0; i < it->text_string.size(); ++i)
		{
			
			if ((it->text_string[i] == '\n'))
			{
				position = it->position;
				position.y -= font->GetFontLineSkip();
				continue;
			}

			auto * glyph = font->GetGlyph(it->text_string[i]);
			
			if ((it->text_string[i] == ' ') && (i < it->text_string.size() - 1))
			{
				position.x += glyph->advance;

				if (i < it->text_string.size() - 1)
				{
					position.x += font->GetKerningDistance(it->text_string[i], it->text_string[i + 1]);
				}

				continue;
			}

			auto * texture = font->GetGlyphTexture(it->text_string[i]);

			if (!texture || !glyph)
			{
				continue;
			}

			glm::vec2 offset;
			offset.x = position.x + glyph->min_x;
			offset.y = position.y;

			glm::mat4 mvp = proj_ *
				glm::translate(glm::mat4(1.0f), glm::vec3(offset, 0.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(glyph->bitmap_width, glyph->bitmap_height, 1.0f));

			default_vert_program_->SetUniform("u_mvp", (void *)&mvp);

			if (texture) 
			{
				glActiveTexture(GL_TEXTURE0 + texture_index);
				glBindTexture(GL_TEXTURE_2D, *texture);  
				default_frag_program_->SetUniform("u_texture", &texture_index);
			}

			FullscreenQuad::Get().DrawElements();

			position.x += glyph->advance;

			if (i < it->text_string.size() - 1)
			{
				position.x += font->GetKerningDistance(it->text_string[i], it->text_string[i + 1]);
			}
		}

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	DataPipeHub::Get().GetTextDataPipe().Flush();

	pipeline_.Unbind();

	FullscreenQuad::Get().End();
}
