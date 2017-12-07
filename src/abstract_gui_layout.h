#pragma once

#include <vector>

#include "abstract_gui_element.h"

namespace core {

	class AbstractGuiLayout
	{
	public:

		AbstractGuiLayout() = default;

		virtual ~AbstractGuiLayout() = default;

		virtual void Arrange(const std::shared_ptr<AbstractGuiElement> &parent, 
			std::vector<std::shared_ptr<AbstractGuiElement>> &elements) = 0;
	};
}
