#pragma once

#include "glm/glm.hpp"

namespace graphics 
{
	enum SpritePrimitive
	{
		Quad,
		Hex,
	};

	struct Sprite
	{
		SpritePrimitive primitive;
		glm::mat4 transform;
		size_t layer;

		Sprite(SpritePrimitive primitive = SpritePrimitive::Quad, 
			const glm::mat4 &transform = glm::mat4(1.0f), size_t layer = 0) :
			primitive(primitive), transform(transform), layer(layer) { }
		
		~Sprite() = default;

		Sprite(const Sprite &other) = default;

		Sprite(Sprite &&other) = default;
	};
}
