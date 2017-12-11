#pragma once

#include "gui_container.h"
#include "application_system_server.h"

namespace core {

	class GuiCanvas : public GuiContainer

	{
	public:

		GuiCanvas(const ApplicationSystemServer &server);

		~GuiCanvas();

		virtual GuiData GetRenderData() override;

		virtual glm::vec2 GetPreferredSize() override;
	};
}