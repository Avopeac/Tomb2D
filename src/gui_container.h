#pragma once

#include <deque>
#include <vector>

#include "abstract_gui_element.h"

namespace graphics {

	struct GuiHit
	{
		std::weak_ptr<AbstractGuiElement> element;
		glm::ivec2 hit;
	};

	class GuiContainer : public AbstractGuiElement
	{
		std::string texture_name_;



	public:

		GuiContainer(const glm::vec2 &size, const std::string &texture_name); 

		~GuiContainer();

		void HitTest(const glm::ivec2 &point, std::deque<GuiHit> &hit_queue);
	};
}
