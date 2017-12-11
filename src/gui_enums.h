#pragma once

namespace core {

	enum class GuiElementType
	{
		Canvas,
		Container,
		Leaf,
	};

	enum class GuiSizeProperty
	{
		Auto,
		Fill,
		Absolute,
	};

	enum class GuiHorizontalAlignmentProperty
	{
		Left,
		Right,
		Center,
	};

	enum class GuiVerticalAlignmentProperty
	{
		Top,
		Bottom,
		Center,
	};
}
