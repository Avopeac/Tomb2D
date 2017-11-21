#pragma once

#include "glm/glm.hpp"

#include "SDL.h"

#include "graphics.h"

#include "resource_manager.h"

namespace graphics 
{
	class FontRenderer
	{
		const GraphicsBase &graphics_base_;

		ProgramPipeline pipeline_;

		Program * default_vert_program_;

		Program * default_frag_program_;

		glm::mat4 proj_;

	public:

		FontRenderer(const GraphicsBase &graphics_base);

		~FontRenderer();

		void Draw(float delta_time);

	private:


	};
}
