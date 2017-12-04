#pragma once

#include <glm/glm.hpp>

#include "abstract_gui_element.h"
#include "application_system_server.h"
#include "sprite_data_message_queue.h"
#include "text_data_message_queue.h"

namespace core {

	class GuiTree
	{
		size_t uid_counter_ = 0;

		AbstractGuiElement * root_ = nullptr;

		const ApplicationSystemServer &server_;

		SpriteDataMessageQueue &sprite_;

		TextDataMessageQueue &text_;

	public:

		GuiTree(const ApplicationSystemServer &server,
			SpriteDataMessageQueue &sprite,
			TextDataMessageQueue &text);

		~GuiTree();

		void Update(float delta_time);
	};
}
