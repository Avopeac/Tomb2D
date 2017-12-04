#pragma once

#include <deque>
#include <vector>

#include "abstract_gui_element.h"

namespace core {

	class GuiContainer : public AbstractGuiElement
	{
		std::string texture_name_;

		glm::vec2 size_;

	public:

		GuiContainer(const glm::vec2 &size, const std::string &texture_name); 

		~GuiContainer();

	};
}
