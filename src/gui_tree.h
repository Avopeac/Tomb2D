#pragma once

#include <glm/glm.hpp>

#include "abstract_gui_element.h"
#include "application_system_server.h"
#include "gui_data_message_queue.h"

namespace core {

	class GuiTree
	{
		AbstractGuiElement * root_ = nullptr;

		const ApplicationSystemServer &server_;
		
		GuiDataMessageQueue &gui_queue_;

	public:

		GuiTree(const ApplicationSystemServer &server,
			GuiDataMessageQueue &gui_queue);

		~GuiTree();

		void Update(float delta_time);

	private:

		void DrawElement(const std::shared_ptr<AbstractGuiElement> &container);
	};
}
