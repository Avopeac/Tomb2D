#pragma once

#include <glm/glm.hpp>

#include "resource_core_system.h"
#include "abstract_data_message_queue.h"

namespace core {
	
	struct GuiData
	{
		size_t sampler_hash;
		size_t blend_hash;
		size_t texture_hash;
		size_t font_hash;
		std::string text;
		glm::vec2 text_scale;
		glm::vec3 text_position;
		glm::mat4 sprite_transform;
		glm::vec4 color;
	};

	class GuiDataMessageQueue : public AbstractDataMessageQueue<GuiData>
	{
	public:

		GuiDataMessageQueue() {}

		~GuiDataMessageQueue() {}
	};
}

