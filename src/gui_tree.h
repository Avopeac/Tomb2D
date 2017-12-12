#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "gui_container.h"
#include "application_system_server.h"
#include "gui_data_message_queue.h"

namespace core {

	class GuiTree
	{
		std::vector<std::shared_ptr<GuiContainer>> top_containers_;

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
