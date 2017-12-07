#pragma once

#include <glm/glm.hpp>

#include "gui_container.h"
#include "gui_data_message_queue.h"

namespace core {

	class GuiPanel : public GuiContainer
	{
		glm::vec4 color_;
		std::string texture_path_ = "assets/textures/white2x2.png";
		Wrapping s_wrapping_ = Wrapping::ClampToEdge;
		Wrapping t_wrapping_ = Wrapping::ClampToEdge;
		BlendMode src_blend_ = BlendMode::SrcAlpha;
		BlendMode dst_blend_ = BlendMode::OneMinusSrcAlpha;
		MagnificationFiltering mag_filter_ = MagnificationFiltering::Linear;
		MinificationFiltering min_filter_ = MinificationFiltering::LinearMipmapLinear;

	public:

		GuiPanel();

		~GuiPanel();

		void SetWrappingS(Wrapping wrapping);

		Wrapping GetWrappingS() const;

		void SetWrappingT(Wrapping wrapping);

		Wrapping GetWrappingT() const;

		void SetBlendModeSrc(BlendMode mode);

		BlendMode GetBlendModeSrc() const;

		void SetBlendModeDst(BlendMode mode);

		BlendMode GetBlendModeDst() const;

		void SetMagFilter(MagnificationFiltering filter);

		MagnificationFiltering GetMagFilter() const;

		void SetMinFilter(MinificationFiltering filter);
		
		MinificationFiltering GetMinFilter() const;

		void SetTexturePath(const std::string &texture_path);

		const std::string &GetTexturePath() const;
		
		void SetColor(const glm::vec4 &color_tint);

		const glm::vec4 &GetColor() const;
	};
}

