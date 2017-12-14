#include "abstract_gui_element.h"

using namespace core;

size_t AbstractGuiElement::uid_counter_ = 0;

AbstractGuiElement::AbstractGuiElement(GuiElementType type) :
	uid_(uid_counter_++), type_(type)
{
}

void AbstractGuiElement::SetPreferredSizeRelative(const glm::vec2 & preferred_size)
{
	preferred_relative_size_ = preferred_size;
}

glm::vec2 AbstractGuiElement::GetPreferredSizeRelative()
{
	return preferred_relative_size_;
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

bool AbstractGuiElement::IsArranged() const
{
	return has_arranged_size_ && has_arranged_position_;
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
	has_arranged_size_ = true;
	arranged_size_ = arranged_size;
}

void AbstractGuiElement::SetArrangedPosition(const glm::vec2 & arranged_position)
{
	has_arranged_position_ = true;
	arranged_position_ = arranged_position;
}

void AbstractGuiElement::SetOffsetToElement(const std::shared_ptr<AbstractGuiElement>& offset_element, 
	GuiVerticalAnchorPoint offset_vertical_anchor, GuiHorizontalAnchorPoint offset_horizontal_anchor)
{
	offset_element_ = offset_element;
	offset_vertical_anchor_ = offset_vertical_anchor;
	offset_horizontal_anchor_ = offset_horizontal_anchor;
}

const std::shared_ptr<AbstractGuiElement>& AbstractGuiElement::GetOffsetElement() const
{
	return offset_element_;
}

GuiVerticalAnchorPoint core::AbstractGuiElement::GetOffsetVerticalAnchor() const
{
	return offset_vertical_anchor_;
}

GuiHorizontalAnchorPoint AbstractGuiElement::GetOffsetHorizontalAnchor() const
{
	return offset_horizontal_anchor_;
}
