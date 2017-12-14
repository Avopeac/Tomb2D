#pragma once

#include <glm/glm.hpp>

#include "gui_image.h"
#include "gui_container.h"
#include "gui_data_message_queue.h"

namespace core {

	class GuiPanel : public GuiContainer
	{

	public:

		GuiPanel(const GuiContainer * const parent);

		~GuiPanel();
	};
}

