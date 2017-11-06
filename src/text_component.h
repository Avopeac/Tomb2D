#pragma once
#pragma once

#include <glm/glm.hpp>
#include <string>

#include "component.h"
#include "resource_manager.h"
#include "text_data_pipe.h"

namespace entity
{
	class TextComponent : public Component
	{

		std::string font_path_;
		glm::vec2 font_scale_;
		glm::vec2 font_position_;
		uint32_t font_width_;
		uint32_t font_height_;

		std::string text_;

		graphics::BlendMode src_blend_;
		graphics::BlendMode dst_blend_;
		graphics::MagnificationFiltering mag_filter_;
		graphics::MinificationFiltering min_filter_;
		graphics::Wrapping s_wrapping_;
		graphics::Wrapping t_wrapping_;

		size_t font_hash_ = 0;
		size_t blend_hash_ = 0;
		size_t sampler_hash_ = 0;

		bool dirty_ = true;

	public:

		TextComponent(const std::string &font_path,
			uint32_t width,
			uint32_t height,
			const std::string &text,
			const glm::vec2 &scale = glm::vec2(1.0f),
			const glm::vec2 &position = glm::vec2(0.0f),
			graphics::BlendMode src_blend = graphics::BlendMode::SrcAlpha,
			graphics::BlendMode dst_blend = graphics::BlendMode::OneMinusSrcAlpha,
			graphics::MagnificationFiltering magnification = graphics::MagnificationFiltering::Linear,
			graphics::MinificationFiltering minification = graphics::MinificationFiltering::Linear,
			graphics::Wrapping s = graphics::Wrapping::ClampToEdge,
			graphics::Wrapping t = graphics::Wrapping::ClampToEdge) :
			font_path_(font_path),
			font_width_(width),
			font_height_(height),
			font_scale_(scale),
			font_position_(position),
			text_(text),
			src_blend_(src_blend),
			dst_blend_(dst_blend),
			mag_filter_(magnification),
			min_filter_(minification),
			s_wrapping_(s),
			t_wrapping_(t)
		{
		}

		virtual ~TextComponent() {}

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

		inline const std::string &GetFontPath() const { return font_path_; }

		inline void SetFontPath(const std::string &path)
		{
			dirty_ = true;
			font_path_ = path;
		}

		inline void SetFontSize(uint32_t width, uint32_t height)
		{
			font_width_ = width;
			font_height_ = height;
		}

		inline uint32_t GetFontWidth() const { return font_width_; }

		inline uint32_t GetFontHeight() const { return font_height_; }

		inline const std::string &GetText() const { return text_; }

		inline void SetText(const std::string &text) { text_ = text; }
		
		inline size_t GetFontHash() const { return font_hash_; }

		inline void SetFontHash(size_t hash) { font_hash_ = hash; }

		inline size_t GetBlendHash() const { return blend_hash_; }

		inline void SetBlendHash(size_t hash) { blend_hash_ = hash; }

		inline size_t GetSamplerHash() const { return sampler_hash_; }

		inline void SetSamplerHash(size_t hash) { sampler_hash_ = hash; }

		inline const glm::vec2 &GetFontScale() const { return font_scale_; }

		inline void SetFontScale(const glm::vec2 &scale) { font_scale_ = scale; }

		inline const glm::vec2 &GetFontPosition() const { return font_position_; }

		inline void SetFontPosition(const glm::vec2 &position) { font_position_ = position; }
	};
}
