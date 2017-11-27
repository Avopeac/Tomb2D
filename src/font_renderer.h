#pragma once

#include "glm/glm.hpp"

#include "SDL.h"

#include "graphics.h"

#include "core.h"

namespace graphics 
{
	class FontRenderer
	{
		const GraphicsBase &graphics_base_;

		core::ProgramPipeline pipeline_;

		core::Program * default_vert_program_;

		core::Program * default_frag_program_;

		glm::mat4 proj_;

	public:

		FontRenderer(const GraphicsBase &graphics_base);

		~FontRenderer();

		void Draw(float delta_time);

	private:


	};
}
