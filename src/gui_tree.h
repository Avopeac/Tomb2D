#pragma once

#include <glm/glm.hpp>

#include "abstract_gui_element.h"

namespace core {

	class GuiTree
	{

		AbstractGuiElement * root_ = nullptr;

	public:

		GuiTree();

		~GuiTree();

		void Update(float delta_time);
	};
}
