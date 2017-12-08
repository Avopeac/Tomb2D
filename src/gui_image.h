#pragma once

#include <glm/glm.hpp>

#include "gui_container.h"

namespace core {

	class GuiImage
	{
		glm::vec4 color_;

		std::string texture_path_ = "assets/textures/white2x2.png";

		BlendMode src_blend_ = BlendMode::SrcAlpha;
		BlendMode dst_blend_ = BlendMode::OneMinusSrcAlpha;
		
		Wrapping s_wrapping_ = Wrapping::ClampToEdge;
		Wrapping t_wrapping_ = Wrapping::ClampToEdge;
		MagnificationFiltering mag_filter_ = MagnificationFiltering::Linear;
		MinificationFiltering min_filter_ = MinificationFiltering::LinearMipmapLinear;

	public:

		GuiImage() = default;

		~GuiImage() = default;

		Wrapping GetWrappingS() const;

		Wrapping GetWrappingT() const;

		MagnificationFiltering GetMagFilter() const;

		MinificationFiltering GetMinFilter() const;

		void SetSampler(Wrapping s_wrapping, Wrapping t_wrapping,
			MagnificationFiltering magnification,
			MinificationFiltering minification);

		BlendMode GetBlendModeSrc() const;

		BlendMode GetBlendModeDst() const;

		void SetBlendMode(BlendMode src, BlendMode dst);

		void SetTexturePath(const std::string &texture_path);

		const std::string &GetTexturePath() const;

		void SetColor(const glm::vec4 &color);

		const glm::vec4 &GetColor() const;
	};
}
