#pragma once

#include <vector>

#include "glm/glm.hpp"

namespace core {

	enum SpriteShape : uint8_t
	{
		Quad = 0 << 0,
		FlatHex = 1 << 0,
		SharpHex = 1 << 1,
		IsometricQuad = 1 << 2,
	};

	struct SpriteData
	{
		size_t texture_hash;
		size_t blend_hash;
		size_t sampler_hash;
		size_t sprite_layer;
		SpriteShape sprite_shape;
		glm::vec4 sprite_color;
		glm::vec4 sprite_animation;
		glm::mat4 sprite_transform;
	};

	class SpriteDataPipe
	{

		std::vector<SpriteData> data_;

	public:

		SpriteDataPipe() {}

		~SpriteDataPipe() {}

		void Push(const SpriteData &sprite_data)
		{
			data_.push_back(sprite_data);
		}

		void Flush()
		{
			data_.clear();
		}

		inline const std::vector<SpriteData> &GetData() const { return data_; }
	};
}
