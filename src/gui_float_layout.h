#pragma once

#include "abstract_gui_layout.h"

namespace core {

	enum class GuiFloatLayoutType
	{
		FloatLeft,
		FloatRight,
	};

	class GuiFloatLayout : public AbstractGuiLayout
	{
	public:

		GuiFloatLayout() = default;

		~GuiFloatLayout() = default;

		// Inherited via AbstractGuiLayout
		virtual void Arrange(const std::shared_ptr<AbstractGuiElement> &parent,
			std::vector<std::shared_ptr<AbstractGuiElement>>& elements) override;

	};
}
