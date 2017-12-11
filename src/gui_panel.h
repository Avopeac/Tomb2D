#pragma once

#include <glm/glm.hpp>

#include "gui_image.h"
#include "gui_container.h"
#include "gui_data_message_queue.h"

namespace core {

	class GuiPanel : public GuiContainer
	{
		GuiImage image_;

	public:

		GuiPanel(const GuiContainer * const parent, GuiImage image);

		~GuiPanel();

		virtual GuiData GetRenderData() override;

		// Inherited via GuiContainer
		virtual glm::vec2 GetPreferredSize() override;
	};
}

