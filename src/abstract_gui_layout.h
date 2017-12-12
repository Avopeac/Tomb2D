#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "abstract_gui_element.h"

namespace core {

	class  AbstractGuiLayout
	{
	public:

		AbstractGuiLayout() = default;

		virtual ~AbstractGuiLayout() = default;

		virtual void Arrange(std::vector<std::shared_ptr<AbstractGuiElement>> &children, 
			const glm::vec2 &parent_position, const glm::vec2 &parent_size) = 0;
	};
}
