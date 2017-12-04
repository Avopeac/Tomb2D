#pragma once

#include <deque>
#include <vector>

#include "abstract_gui_element.h"

namespace core {

	class GuiContainer : public AbstractGuiElement
	{
		std::string texture_name_ = "";

		glm::vec2 size_ = { 1, 1 };

		bool visible_ = false;

	public:

		GuiContainer(size_t uid, const glm::vec2 &size, const std::string &texture_name); 

		~GuiContainer();

		void SetVisible(bool visible) { visible_ = visible; }

		bool IsVisible() const { return visible_; }

		const std::string &GetTextureName() const { return texture_name_; }

		const glm::vec2 &GetSize() const { return size_; }
	};
}
