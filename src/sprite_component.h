#pragma once
#pragma once

#include <glm/glm.hpp>
#include <string>

#include "component.h"
#include "sprite_data_pipe.h"
#include "resource_core_system.h"

namespace game
{
	class SpriteComponent : public core::Component
	{

		bool dirty_ = true;

		std::string texture_path_;

		core::BlendMode src_blend_;
		core::BlendMode dst_blend_;
		core::MagnificationFiltering mag_filter_;
		core::MinificationFiltering min_filter_;
		core::Wrapping s_wrapping_;
		core::Wrapping t_wrapping_;

		size_t layer_;
		glm::vec4 color_;
		glm::mat4 transform_;
		core::SpriteShape shape_;

		size_t texture_hash_ = 0;
		size_t blend_hash_ = 0;
		size_t sampler_hash_ = 0;

	public:

		SpriteComponent(const std::string &texture_path, 
			const glm::vec4 &color = glm::vec4(1.0f),
			const glm::mat4 &transform = glm::mat4(1.0f),
			size_t layer = 0,
			core::SpriteShape shape = core::SpriteShape::Quad,
			core::BlendMode src_blend = core::BlendMode::SrcAlpha,
			core::BlendMode dst_blend = core::BlendMode::OneMinusSrcAlpha,
			core::MagnificationFiltering magnification = core::MagnificationFiltering::Linear,
			core::MinificationFiltering minification = core::MinificationFiltering::Linear,
			core::Wrapping s = core::Wrapping::ClampToEdge,
			core::Wrapping t = core::Wrapping::ClampToEdge) :
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
		
		inline core::BlendMode GetSrcBlend() const { return src_blend_; }

		inline void SetSrcBlend(core::BlendMode blend_mode)
		{
			dirty_ = true;
			dst_blend_ = blend_mode;
		}

		inline core::BlendMode GetDstBlend() const { return dst_blend_; }

		inline void SetDstBlend(core::BlendMode blend_mode)
		{
			dirty_ = true;
			dst_blend_ = blend_mode;
		}

		inline core::MinificationFiltering GetMinFilter() const { return min_filter_; }

		inline void SetMinFilter(core::MinificationFiltering filter)
		{
			dirty_ = true;
			min_filter_ = filter;
		}

		inline core::MagnificationFiltering GetMagFilter() const { return mag_filter_; }

		inline void SetMagFilter(core::MagnificationFiltering filter)
		{
			dirty_ = true;
			mag_filter_ = filter;
		}

		inline core::Wrapping GetWrappingS() const { return s_wrapping_; }

		inline void SetWrappingS(core::Wrapping wrap_mode)
		{
			dirty_ = true;
			s_wrapping_ = wrap_mode;
		}

		inline core::Wrapping GetWrappingT() const { return t_wrapping_; }

		inline void SetWrappingT(core::Wrapping wrap_mode)
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

		inline core::SpriteShape GetShape() const { return shape_; }

		inline void SetShape(core::SpriteShape shape) {	shape_ = shape;	}

		inline size_t GetTextureHash() const { return texture_hash_; }

		inline void SetTextureHash(size_t hash) { texture_hash_ = hash; }

		inline size_t GetBlendHash() const { return blend_hash_; }

		inline void SetBlendHash(size_t hash) { blend_hash_ = hash; }

		inline size_t GetSamplerHash() const { return sampler_hash_; }

		inline void SetSamplerHash(size_t hash) { sampler_hash_ = hash; }
	};
}
