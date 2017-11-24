#pragma once

#include "glm/glm.hpp"

#include "graphics.h"

#include "abstract_gui_element.h"

namespace graphics {

	class GuiTree
	{

		const GraphicsBase * graphics_base_;

		AbstractGuiElement * root_;

	public:

		GuiTree(const GraphicsBase &graphics_base);

		~GuiTree();

		void Render();

		void Update(float delta_time);

	private:

		Interaction GetHitInteraction();

		Interaction GetHoverInteraction();

		Interaction GetDehoverInteraction();

	};
}
