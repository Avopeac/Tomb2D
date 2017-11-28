#pragma once

#include "glm/glm.hpp"

#include "SDL.h"

#include "core.h"

namespace core
{
	class FontRenderer
	{
		ProgramPipeline pipeline_;

		Program * default_vert_program_;

		Program * default_frag_program_;

		glm::mat4 proj_;

	public:

		FontRenderer();

		~FontRenderer();

		void Draw(float delta_time);

	private:


	};
}
