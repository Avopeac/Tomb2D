#pragma once

#include <glm/glm.hpp>
#include <SDL.h>

#include "render_quad.h"
#include "resource_core_system.h"
#include "graphics_core_system.h"
#include "text_data_message_queue.h"

namespace core
{
	class FontRenderer
	{
		ProgramPipeline pipeline_;
		Program * default_vert_program_;
		Program * default_frag_program_;

		RenderQuad &quad_;
		ResourceCoreSystem &resource_core_;
		GraphicsCoreSystem &graphics_core_;
		TextDataMessageQueue &queue_;

		glm::mat4 proj_;

	public:

		FontRenderer(TextDataMessageQueue &text_queue, 
			RenderQuad &quad, ResourceCoreSystem &resource_core, GraphicsCoreSystem &graphics_core);

		~FontRenderer();

		void Draw(float delta_time);
	};
}
