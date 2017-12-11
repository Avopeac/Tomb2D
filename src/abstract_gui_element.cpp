#include "abstract_gui_element.h"

using namespace core;

size_t AbstractGuiElement::uid_counter_ = 0;

AbstractGuiElement::AbstractGuiElement(GuiElementType type) :
	uid_(uid_counter_++), type_(type)
{
}

GuiVerticalAlignmentProperty AbstractGuiElement::GetVerticalAlignmentProperty() const
{
	return vertical_alignment_;
}

GuiHorizontalAlignmentProperty AbstractGuiElement::GetHorizontalAlignmentProperty() const
{
	return horizontal_alignment_;
}

GuiSizeProperty AbstractGuiElement::GetWidthProperty() const
{
	return width_property_;
}

GuiSizeProperty AbstractGuiElement::GetHeightProperty() const
{
	return height_property_;
}

GuiElementType AbstractGuiElement::GetType() const
{
	return type_;
}

size_t AbstractGuiElement::GetUniqueId() const
{
	return uid_;
}

bool AbstractGuiElement::IsVisible() const
{
	return visible_;
}

const glm::vec2 & AbstractGuiElement::GetArrangedSize() const
{
	return arranged_size_;
}

const glm::vec2 & AbstractGuiElement::GetArrangedPosition() const
{
	return arranged_position_;
}

void AbstractGuiElement::SetVisible(bool visible)
{
	visible_ = visible;
}

void AbstractGuiElement::SetHeightProperty(GuiSizeProperty height)
{
	height_property_ = height;
}

void AbstractGuiElement::SetWidthProperty(GuiSizeProperty width)
{
	width_property_ = width;
}

void AbstractGuiElement::SetVerticalAlignmentProperty(GuiVerticalAlignmentProperty alignment)
{
	vertical_alignment_ = alignment;
}

void AbstractGuiElement::SetHorizontalAlignmentProperty(GuiHorizontalAlignmentProperty alignment)
{
	horizontal_alignment_ = alignment;
}

void AbstractGuiElement::SetArrangedSize(const glm::vec2 & arranged_size)
{
	arranged_size_ = arranged_size;
}

void AbstractGuiElement::SetArrangedPosition(const glm::vec2 & arranged_position)
{
	arranged_position_ = arranged_position;
}
