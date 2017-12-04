#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "abstract_data_message_queue.h"

namespace core {

	struct SpriteData
	{
		size_t texture_hash;
		size_t blend_hash;
		size_t sampler_hash;
		size_t sprite_layer;
		glm::vec4 sprite_color;
		glm::vec4 sprite_animation;
		glm::mat4 sprite_transform;
	};

	class SpriteDataMessageQueue : public AbstractDataMessageQueue<SpriteData>
	{

	public:

		SpriteDataMessageQueue() {}

		~SpriteDataMessageQueue() {}

	};
}
