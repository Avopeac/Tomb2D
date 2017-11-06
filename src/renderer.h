#pragma once

#include <memory>

#include "graphics.h"
#include "resource_manager.h"
#include "post_processing.h"
#include "sprite_renderer.h"
#include "font_renderer.h"

namespace graphics
{
	class Renderer
	{

		GraphicsBase *graphics_base_;
		FrameBuffer *render_target_;

		std::unique_ptr<SpriteRenderer> sprite_renderer_;
		std::unique_ptr<FontRenderer> font_renderer_;
		std::unique_ptr<PostProcessing> post_processing_;

	public:

		static const std::string render_target_name;

		Renderer(GraphicsBase *graphics_base);

		~Renderer();

		inline SpriteRenderer &GetSpriteRenderer() { return *sprite_renderer_; }

		inline FontRenderer &GetFontRenderer() { return *font_renderer_; }

		inline PostProcessing &GetPostProcessing() { return *post_processing_; }

		void Invoke(float frame_time);

	private:

		FrameBuffer* CreateRenderTarget();

	};
}
