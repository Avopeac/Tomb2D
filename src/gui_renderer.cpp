#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gui_renderer.h"
#include "renderer.h"

using namespace core;

GuiRenderer::GuiRenderer(GuiDataMessageQueue & gui_queue, RenderQuad &quad,
	ResourceCoreSystem & resource_core, GraphicsCoreSystem & graphics_core) :
	gui_queue_(gui_queue), quad_(quad), resource_core_(resource_core), graphics_core_(graphics_core)
{
	default_text_vert_program_ = resource_core_.GetProgramCache().GetFromFile("default_font.vert", GL_VERTEX_SHADER, "assets/shaders/default_font.vert");
	default_text_frag_program_ = resource_core_.GetProgramCache().GetFromFile("default_font.frag", GL_FRAGMENT_SHADER, "assets/shaders/default_font.frag");
	default_sprite_vert_program_ = resource_core_.GetProgramCache().GetFromFile("default_gui_sprite.vert", GL_VERTEX_SHADER, "assets/shaders/default_gui_sprite.vert");
	default_sprite_frag_program_ = resource_core_.GetProgramCache().GetFromFile("default_gui_sprite.frag", GL_FRAGMENT_SHADER, "assets/shaders/default_gui_sprite.frag");

	pipeline_.SetStages(*default_text_vert_program_);
	pipeline_.SetStages(*default_text_frag_program_);

	proj_ = glm::ortho(0.0f, float(graphics_core_.GetBackbufferWidth()),
		0.0f, float(graphics_core_.GetBackbufferHeight()),
		-1.0f, 1.0f);
}

GuiRenderer::~GuiRenderer()
{
}

void GuiRenderer::Draw(float delta_time)
{
	FrameBuffer * render_target = resource_core_.GetFrameBufferCache().GetFromName(Renderer::render_target_name);
	render_target->BindDraw(0, 0, 0, 0, 0);

	pipeline_.Bind();
	quad_.Begin();

	GuiData data;
	while (gui_queue_.TryPop(data))
	{
		if (data.text.empty())
		{
			DrawSprite(data);
		}
		else
		{
			DrawText(data);
		}
	}

	quad_.End();
	pipeline_.Unbind();

	render_target->UnbindDraw();
}

void GuiRenderer::DrawText(const GuiData & data)
{
	auto * blend_mode = resource_core_.GetBlendCache().GetFromHash(data.blend_hash);
	auto * font = resource_core_.GetFontCache().GetFromHash(data.font_hash);
	auto * sampler = resource_core_.GetSamplerCache().GetFromHash(data.sampler_hash);

	pipeline_.SetStages(*default_text_vert_program_);
	pipeline_.SetStages(*default_text_frag_program_);
	
	glm::vec2 position = data.text_position;

	int texture_index = 0;
	for (size_t i = 0; i < data.text.size(); ++i)
	{
		if ((data.text[i] == '\n'))
		{
			position = data.text_position;
			position.y -= font->GetFontLineSkip();
			continue;
		}

		auto * glyph = font->GetGlyph(data.text[i]);

		if ((data.text[i] == ' ') && (i < data.text.size() - 1))
		{
			position.x += glyph->advance;

			if (i < data.text.size() - 1)
			{
				position.x += font->GetKerningDistance(data.text[i], data.text[i + 1]);
			}

			continue;
		}

		auto * texture = font->GetGlyphTexture(data.text[i]);

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

		default_text_vert_program_->SetUniform("u_mvp", (void *)&mvp);
		default_text_frag_program_->SetUniform("u_color", (void *)glm::value_ptr(data.color));

		if (texture)
		{
			glActiveTexture(GL_TEXTURE0 + texture_index);
			glBindTexture(GL_TEXTURE_2D, *texture);
			default_text_frag_program_->SetUniform("u_texture", &texture_index);
		}

		quad_.DrawElements();

		position.x += glyph->advance;

		if (i < data.text.size() - 1)
		{
			position.x += font->GetKerningDistance(data.text[i], data.text[i + 1]);
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void GuiRenderer::DrawSprite(const GuiData & data)
{
	auto * blend_mode = resource_core_.GetBlendCache().GetFromHash(data.blend_hash);
	auto * texture = resource_core_.GetTextureCache().GetFromHash(data.texture_hash);
	auto * sampler = resource_core_.GetSamplerCache().GetFromHash(data.sampler_hash);

	pipeline_.SetStages(*default_sprite_vert_program_);
	pipeline_.SetStages(*default_sprite_frag_program_);

	GLenum texture_index = 0;

	glm::mat4 mvp = proj_ * data.sprite_transform;

	default_text_vert_program_->SetUniform("u_mvp", (void *)&mvp);
	default_text_frag_program_->SetUniform("u_color", (void *)glm::value_ptr(data.color));

	if (texture)
	{
		glActiveTexture(GL_TEXTURE0 + texture_index);
		glBindTexture(GL_TEXTURE_2D, texture->GetId());
		default_text_frag_program_->SetUniform("u_texture", &texture_index);
	}

	quad_.DrawElements();
}
