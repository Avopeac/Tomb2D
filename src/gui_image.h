#pragma once

#include <glm/glm.hpp>

#include "gui_leaf.h"
#include "gui_container.h"

namespace core {

	class GuiImage : public GuiLeaf
	{

		size_t blend_hash_;
		size_t texture_hash_;
		size_t sampler_hash_;

		size_t texture_width_;
		size_t texture_height_;
		std::string texture_path_ = "assets/textures/white2x2.png";

		BlendMode src_blend_ = BlendMode::SrcAlpha;
		BlendMode dst_blend_ = BlendMode::OneMinusSrcAlpha;
		Wrapping s_wrapping_ = Wrapping::ClampToEdge;
		Wrapping t_wrapping_ = Wrapping::ClampToEdge;
		MagnificationFiltering mag_filter_ = MagnificationFiltering::Linear;
		MinificationFiltering min_filter_ = MinificationFiltering::LinearMipmapLinear;

	public:

		GuiImage(const GuiContainer * const parent, const ApplicationSystemServer &server, const std::string &texture_path,
			BlendMode src, BlendMode dst, Wrapping s, Wrapping t,
			MagnificationFiltering mag, MinificationFiltering min);

		~GuiImage() = default;

		size_t GetSamplerHash() const;

		size_t GetBlendHash() const;

		size_t GetTextureHash() const;

		Wrapping GetWrappingS() const;

		Wrapping GetWrappingT() const;

		MagnificationFiltering GetMagFilter() const;

		MinificationFiltering GetMinFilter() const;

		BlendMode GetBlendModeSrc() const;

		BlendMode GetBlendModeDst() const;

		const std::string &GetTexturePath() const;

		size_t GetTextureWidth() const;

		size_t GetTextureHeight() const;

		virtual GuiData GetRenderData() override;
	};
}
