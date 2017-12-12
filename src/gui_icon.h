#pragma once

#include "gui_leaf.h"
#include "gui_image.h"

namespace core {

	class GuiIcon : public GuiLeaf
	{

		GuiImage image_;

	public:

		GuiIcon(const GuiContainer * const parent, const GuiImage &image);

		~GuiIcon();

		virtual GuiData GetRenderData() override;

		virtual glm::vec2 GetPreferredSize() override;

		virtual glm::vec2 GetPreferredSizeRelative() override;

	};
}
