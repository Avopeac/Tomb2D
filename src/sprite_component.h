#pragma once
#pragma once

#include <glm/glm.hpp>
#include <string>

#include "component.h"
#include "resource_manager.h"
#include "sprite_data_pipe.h"

namespace entity
{
	class SpriteComponent : public Component
	{

		friend class SpriteRenderSystem;

		std::string texture_path_;
		graphics::BlendMode src_blend_;
		graphics::BlendMode dst_blend_;
		graphics::MagnificationFiltering mag_filter_;
		graphics::MinificationFiltering min_filter_;
		graphics::Wrapping s_wrapping_;
		graphics::Wrapping t_wrapping_;

		size_t sprite_layer_;
		glm::vec4 sprite_color_;
		glm::mat4 sprite_transform_;
		graphics::SpriteShape sprite_shape_;

		size_t texture_hash_ = 0;
		size_t blend_hash_ = 0;
		size_t sampler_hash_ = 0;

	public:

		SpriteComponent(const std::string &texture_path, 
			const glm::vec4 &color = glm::vec4(1.0f),
			const glm::mat4 &transform = glm::mat4(1.0f),
			size_t layer = 0,
			graphics::SpriteShape shape = graphics::SpriteShape::Quad,
			graphics::BlendMode src_blend = graphics::BlendMode::One, 
			graphics::BlendMode dst_blend = graphics::BlendMode::One,
			graphics::MagnificationFiltering magnification = graphics::MagnificationFiltering::Linear,
			graphics::MinificationFiltering minification = graphics::MinificationFiltering::Linear, 
			graphics::Wrapping s = graphics::Wrapping::ClampToEdge,
			graphics::Wrapping t = graphics::Wrapping::ClampToEdge) :
			texture_path_(texture_path),
			src_blend_(src_blend),
			dst_blend_(dst_blend),
			mag_filter_(magnification),
			min_filter_(minification),
			s_wrapping_(s),
			t_wrapping_(t),
			sprite_layer_(layer),
			sprite_shape_(shape),
			sprite_color_(color),
			sprite_transform_(transform)
		{
		}

		virtual ~SpriteComponent() {}

	};
}
