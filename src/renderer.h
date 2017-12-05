#pragma once

#include <memory>

#include "sprite_data_message_queue.h"
#include "text_data_message_queue.h"
#include "gui_data_message_queue.h"
#include "render_quad.h"
#include "post_processing.h"
#include "sprite_renderer.h"
#include "gui_renderer.h"
#include "font_renderer.h"

namespace core
{
	class Renderer
	{

		FrameBuffer *render_target_;

		RenderQuad quad_;

		std::unique_ptr<SpriteRenderer> sprite_renderer_;
		std::unique_ptr<FontRenderer> font_renderer_;
		std::unique_ptr<GuiRenderer> gui_renderer_;
		std::unique_ptr<PostProcessing> post_processing_;

		ResourceCoreSystem &resource_core_;
		GraphicsCoreSystem &graphics_core_;

	public:

		static const std::string render_target_name;

		Renderer(SpriteDataMessageQueue &sprite_queue,
			TextDataMessageQueue &text_queue,
			GuiDataMessageQueue &gui_queue,
			ResourceCoreSystem &resource_core, 
			GraphicsCoreSystem &graphics_core);

		~Renderer();

		void Invoke(float frame_time);

	private:

		FrameBuffer* CreateRenderTarget();

	};
}
