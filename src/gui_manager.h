#pragma once

#include "glm/glm.hpp"

#include "graphics.h"

#include "abstract_gui_element.h"

namespace graphics {

	class GuiManager
	{

		const GraphicsBase * graphics_base_;

		AbstractGuiElement * root_;

	public:

		GuiManager(const GraphicsBase &graphics_base);

		~GuiManager();

		void Render();

		void Update(float delta_time);

	private:

		Interaction GetHitInteraction();

		Interaction GetHoverInteraction();

		Interaction GetDehoverInteraction();


	};
}
