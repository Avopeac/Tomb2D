#pragma once

#include <glm/glm.hpp>

#include "gui_image.h"
#include "gui_container.h"
#include "gui_data_message_queue.h"

namespace core {

	class GuiPanel : public GuiContainer
	{

		bool initialized = false;

		size_t texture_hash_;
		size_t blend_hash_;
		size_t sampler_hash_;

		GuiImage image_;

	public:

		GuiPanel(const GuiContainer * const parent, GuiImage image);

		~GuiPanel();

		virtual GuiData GetRenderData(const ApplicationSystemServer & server) override;
	};
}

