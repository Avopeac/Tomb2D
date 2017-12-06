#pragma once

#include <glm/glm.hpp>

#include "gui_container.h"
#include "gui_data_message_queue.h"

namespace core {

	class GuiPanel : public GuiContainer
	{

	public:

		GuiPanel() = default;

		~GuiPanel() = default;

		void SetSize(const glm::vec2 &size)
		{
			gui_data_.sprite_transform[0][0] = size.x;
			gui_data_.sprite_transform[1][1] = size.y;
		}

		void SetTextureHash(size_t texture_hash)
		{
			gui_data_.texture_hash = texture_hash;
		}
	};
}

