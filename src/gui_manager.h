#pragma once

#include "glm/glm.hpp"

namespace graphics {

	class GuiManager
	{

		glm::ivec2 offset_;
		
		glm::ivec2 size_;


	public:

		GuiManager(const glm::ivec2 &offset, const glm::ivec2 &size);

		~GuiManager();

	};
}
