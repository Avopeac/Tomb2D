#pragma once
#pragma once

#include <glm/glm.hpp>
#include <string>

#include "component.h"
#include "core.h"
#include "text_data_pipe.h"

namespace core
{
	class TextComponent : public Component
	{

		std::string font_path_;
		glm::vec2 font_scale_;
		glm::vec2 font_position_;
		uint32_t font_pt_size_;

		std::string text_;

		core::BlendMode src_blend_;
		core::BlendMode dst_blend_;
		core::MagnificationFiltering mag_filter_;
		core::MinificationFiltering min_filter_;
		core::Wrapping s_wrapping_;
		core::Wrapping t_wrapping_;

		size_t font_hash_ = 0;
		size_t blend_hash_ = 0;
		size_t sampler_hash_ = 0;

		bool dirty_ = true;

	public:

		TextComponent(const std::string &font_path,
			uint32_t font_pt_size,
			const std::string &text,
			const glm::vec2 &scale = glm::vec2(1.0f),
			const glm::vec2 &position = glm::vec2(0.0f),
			core::BlendMode src_blend = core::BlendMode::SrcAlpha,
			core::BlendMode dst_blend = core::BlendMode::OneMinusSrcAlpha,
			core::MagnificationFiltering magnification = core::MagnificationFiltering::Linear,
			core::MinificationFiltering minification = core::MinificationFiltering::Linear,
			core::Wrapping s = core::Wrapping::ClampToEdge,
			core::Wrapping t = core::Wrapping::ClampToEdge) :
			font_path_(font_path),
			font_pt_size_(font_pt_size),
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

		inline const std::string &GetFontPath() const { return font_path_; }

		inline void SetFontPath(const std::string &path)
		{
			dirty_ = true;
			font_path_ = path;
		}

		inline void SetFontPointSize(uint32_t pt_size)
		{
			dirty_ = true;
			font_pt_size_ = pt_size;
		}

		inline uint32_t GetFontPointSize() const { return font_pt_size_; }

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
