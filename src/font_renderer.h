#pragma once

#include "glm/glm.hpp"

#include "SDL.h"

#include "graphics.h"

#include "resource_manager.h"

namespace graphics 
{
	class FontRenderer
	{

		const glm::vec2 quad_vertices_[4] =
		{
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f,  1.0f),
			glm::vec2(1.0f,  1.0f),
		};

		const Uint32 quad_indices_[6] =
		{
			0, 1, 2,
			2, 1, 3
		};

		const GraphicsBase &graphics_base_;

		ProgramPipeline pipeline_;

		Program * default_vert_program_;

		Program * default_frag_program_;

		GLuint vao_, vbo_, ebo_;

		glm::mat4 proj_;

	public:

		FontRenderer(const GraphicsBase &graphics_base);

		~FontRenderer();

		void Draw(float delta_time);

	private:


	};
}
