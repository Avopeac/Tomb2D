#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "abstract_data_message_queue.h"

namespace core {

	struct TextData
	{
		size_t font_hash;
		size_t blend_hash;
		size_t sampler_hash;
		glm::vec2 scale;
		glm::vec2 position;
		std::string text_string;
	};

	class TextDataMessageQueue : public AbstractDataMessageQueue<TextData>
	{

	public:

		TextDataMessageQueue() {}

		~TextDataMessageQueue() {}
	};
}
