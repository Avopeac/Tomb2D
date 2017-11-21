#pragma once

#include "glm/glm.hpp"

#include "abstract_gui_object.h"

namespace graphics {

	class GuiCanvas : public AbstractGuiObject
	{
	public:

		GuiCanvas(const glm::ivec2 &offset, const glm::ivec2 &size);

		~GuiCanvas();

	};
}
