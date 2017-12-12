#pragma once

#include "gui_container.h"

namespace core {

	class GuiLeaf : public AbstractGuiElement
	{
		const GuiContainer * const parent_ = nullptr;

	public:

		GuiLeaf(const GuiContainer * const parent);

		virtual ~GuiLeaf();

	};
}
