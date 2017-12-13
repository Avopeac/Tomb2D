#include "abstract_gui_element.h"

using namespace core;

size_t AbstractGuiElement::uid_counter_ = 0;

AbstractGuiElement::AbstractGuiElement(GuiElementType type) :
	uid_(uid_counter_++), type_(type)
{
}

GuiElementType AbstractGuiElement::GetType() const
{
	return type_;
}

GuiVerticalAnchorPoint AbstractGuiElement::GetVerticalAnchorPoint() const
{
	return vertical_anchor_;
}

GuiHorizontalAnchorPoint AbstractGuiElement::GetHorizontalAnchorPoint() const
{
	return horizontal_achor_;
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

void AbstractGuiElement::SetVerticalAnchorPoint(GuiVerticalAnchorPoint anchor)
{
	vertical_anchor_ = anchor;
}

void AbstractGuiElement::SetHorizontalAnchorPoint(GuiHorizontalAnchorPoint anchor)
{
	horizontal_achor_ = anchor;
}

void AbstractGuiElement::SetArrangedSize(const glm::vec2 & arranged_size)
{
	arranged_size_ = arranged_size;
}

void AbstractGuiElement::SetArrangedPosition(const glm::vec2 & arranged_position)
{
	arranged_position_ = arranged_position;
}
