#pragma once

#include <string>
#include <glm/glm.hpp>

#include "resource_core_system.h"

namespace core {

	struct GuiDrawData
	{
		bool visible = false;
		glm::vec2 size = { 0, 0 };
		std::string texture_name = "";
		MagnificationFiltering mag_filter = MagnificationFiltering::Linear;
		MinificationFiltering min_filter = MinificationFiltering::LinearMipmapLinear;
		Wrapping s_wrapping = Wrapping::ClampToEdge;
		Wrapping t_wrapping = Wrapping::ClampToEdge;
		BlendMode src_blend = BlendMode::SrcAlpha;
		BlendMode dst_blend = BlendMode::OneMinusSrcAlpha;
	};
}
