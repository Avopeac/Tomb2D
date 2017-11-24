#pragma once

#include "abstract_gui_element.h"

namespace graphics {

	class GuiPanel : public AbstractGuiElement
	{

		std::string texture_name_;

	public:

		GuiPanel(const glm::vec2 &size, const std::string &texture_name); 

		~GuiPanel();
	};
}
