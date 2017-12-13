#pragma once

#include <glm/glm.hpp>

#include "gui_container.h"
#include "gui_data_message_queue.h"

namespace core {

	class GuiPanel : public GuiContainer
	{
		glm::vec2 relative_size_;
		glm::vec2 preferred_size_;

	public:

		GuiPanel(const GuiContainer * const parent);

		~GuiPanel();

		void SetPreferredSize(const glm::vec2 &preferred_size);

		void SetPreferredSizeRelative(const glm::vec2 &preferred_size);

		virtual glm::vec2 GetPreferredSize() override;

		virtual glm::vec2 GetPreferredSizeRelative() override;
	};
}

