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

		bool dirty_ = true;

		std::string texture_path_;

		graphics::BlendMode src_blend_;
		graphics::BlendMode dst_blend_;
		graphics::MagnificationFiltering mag_filter_;
		graphics::MinificationFiltering min_filter_;
		graphics::Wrapping s_wrapping_;
		graphics::Wrapping t_wrapping_;

		size_t layer_;
		glm::vec4 color_;
		glm::mat4 transform_;
		graphics::SpriteShape shape_;

		size_t texture_hash_ = 0;
		size_t blend_hash_ = 0;
		size_t sampler_hash_ = 0;

	public:

		SpriteComponent(const std::string &texture_path, 
			const glm::vec4 &color = glm::vec4(1.0f),
			const glm::mat4 &transform = glm::mat4(1.0f),
			size_t layer = 0,
			graphics::SpriteShape shape = graphics::SpriteShape::Quad,
			graphics::BlendMode src_blend = graphics::BlendMode::SrcAlpha, 
			graphics::BlendMode dst_blend = graphics::BlendMode::OneMinusSrcAlpha,
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
			layer_(layer),
			shape_(shape),
			color_(color),
			transform_(transform)
		{
		}

		virtual ~SpriteComponent() {}

		inline bool IsDirty() { return dirty_; }

		void LowerDirty() { dirty_ = false; }
		
		inline graphics::BlendMode GetSrcBlend() const { return src_blend_; }

		inline void SetSrcBlend(graphics::BlendMode blend_mode)
		{
			dirty_ = true;
			dst_blend_ = blend_mode;
		}

		inline graphics::BlendMode GetDstBlend() const { return dst_blend_; }

		inline void SetDstBlend(graphics::BlendMode blend_mode)
		{
			dirty_ = true;
			dst_blend_ = blend_mode;
		}

		inline graphics::MinificationFiltering GetMinFilter() const { return min_filter_; }

		inline void SetMinFilter(graphics::MinificationFiltering filter)
		{
			dirty_ = true;
			min_filter_ = filter;
		}

		inline graphics::MagnificationFiltering GetMagFilter() const { return mag_filter_; }

		inline void SetMagFilter(graphics::MagnificationFiltering filter)
		{
			dirty_ = true;
			mag_filter_ = filter;
		}

		inline graphics::Wrapping GetWrappingS() const { return s_wrapping_; }

		inline void SetWrappingS(graphics::Wrapping wrap_mode)
		{
			dirty_ = true;
			s_wrapping_ = wrap_mode;
		}

		inline graphics::Wrapping GetWrappingT() const { return t_wrapping_; }

		inline void SetWrappingT(graphics::Wrapping wrap_mode)
		{
			dirty_ = true;
			t_wrapping_ = wrap_mode;
		}

		inline const std::string &GetTexturePath() const { return texture_path_; }

		inline void SetTexturePath(const std::string &path)
		{
			dirty_ = true;
			texture_path_ = path;
		}

		inline const glm::vec4 &GetColor() const { return color_; }

		inline void SetColor(const glm::vec4 &color) { color_ = color; }

		inline const glm::mat4 &GetTransform() const { return transform_; }

		inline void SetTransform(const glm::mat4 &transform) { transform_ = transform; }

		inline size_t GetLayer() const { return layer_; }

		inline void SetLayer(size_t layer) { layer_ = layer; }

		inline graphics::SpriteShape GetShape() const { return shape_; }

		inline void SetShape(graphics::SpriteShape shape) {	shape_ = shape;	}

		inline size_t GetTextureHash() const { return texture_hash_; }

		inline void SetTextureHash(size_t hash) { texture_hash_ = hash; }

		inline size_t GetBlendHash() const { return blend_hash_; }

		inline void SetBlendHash(size_t hash) { blend_hash_ = hash; }

		inline size_t GetSamplerHash() const { return sampler_hash_; }

		inline void SetSamplerHash(size_t hash) { sampler_hash_ = hash; }
	};
}
