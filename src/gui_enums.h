#pragma once

namespace core {

	enum class GuiElementType
	{
		Container,
		Leaf,
	};

	enum class GuiSizeProperty
	{
		Auto,
		Fill,
		Absolute,
		Relative,
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
