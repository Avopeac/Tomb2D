#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "gui_data_message_queue.h"
#include "resource_core_system.h"
#include "graphics_core_system.h"
#include "render_quad.h"

namespace core {

	class GuiRenderer
	{
		glm::mat4 proj_;

		RenderQuad &quad_;

		ProgramPipeline pipeline_;
		Program * default_sprite_vert_program_;
		Program * default_sprite_frag_program_;
		Program * default_text_vert_program_;
		Program * default_text_frag_program_;

		GuiDataMessageQueue &gui_queue_;
		ResourceCoreSystem &resource_core_;
		GraphicsCoreSystem &graphics_core_;

	public:

		GuiRenderer(GuiDataMessageQueue &gui_queue, RenderQuad &quad,
			ResourceCoreSystem &resource_core, GraphicsCoreSystem &graphics_core);

		~GuiRenderer();

		void Draw(float delta_time);

	private:

		void DrawText(const GuiData &data);

		void DrawSprite(const GuiData &data);
	};
}
