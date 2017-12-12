#pragma once

#include <glm/glm.hpp>

#include "gui_image.h"
#include "gui_container.h"
#include "gui_data_message_queue.h"

namespace core {

	class GuiPanel : public GuiContainer
	{
		glm::vec2 relative_size_;
		glm::vec2 preferred_size_;

		GuiImage image_;

	public:

		GuiPanel(const GuiContainer * const parent, GuiImage image);

		~GuiPanel();

		void SetPreferredSize(const glm::vec2 &preferred_size);

		void SetPreferredSizeRelative(const glm::vec2 &preferred_size);

		virtual GuiData GetRenderData() override;

		virtual glm::vec2 GetPreferredSize() override;

		virtual glm::vec2 GetPreferredSizeRelative() override;
	};
}

