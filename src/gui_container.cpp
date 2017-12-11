#include "gui_container.h"

using namespace core;

GuiContainer::GuiContainer(const GuiContainer * const parent) :
	AbstractGuiElement(GuiElementType::Container), parent_(parent)
{
}

GuiContainer::~GuiContainer()
{
}

void GuiContainer::Arrange()
{
	glm::vec2 parent_size = GetArrangedSize();
	glm::vec2 parent_pos = GetArrangedPosition();

	for (auto it = children_.begin(); it != children_.end(); ++it)
	{
		AbstractGuiElement * abstract_element = (*it).get();

		glm::vec2 child_preferred_size = abstract_element->GetPreferredSize();
		glm::vec2 child_pos = parent_pos;
		glm::vec2 child_size = child_preferred_size;

		auto halign = abstract_element->GetHorizontalAlignmentProperty();
		auto valign = abstract_element->GetVerticalAlignmentProperty();
		auto hsize = abstract_element->GetWidthProperty();
		auto vsize = abstract_element->GetHeightProperty();

		if (hsize == GuiSizeProperty::Absolute)
		{

		}
		else if (hsize == GuiSizeProperty::Auto)
		{

		}
		else if (hsize == GuiSizeProperty::Fill)
		{
			child_size.x = parent_size.x;
		}

		if (vsize == GuiSizeProperty::Absolute)
		{

		}
		else if (vsize == GuiSizeProperty::Auto)
		{

		}
		else if (vsize == GuiSizeProperty::Fill)
		{
			child_size.y = parent_size.y;
		}

		if (halign == GuiHorizontalAlignmentProperty::Left)
		{
			child_pos.x = parent_pos.x;
		}
		else if (halign == GuiHorizontalAlignmentProperty::Right)
		{
			child_pos.x = (parent_pos.x + parent_size.x) - child_size.x;
		}
		else if (halign == GuiHorizontalAlignmentProperty::Center)
		{
			child_pos.x = (parent_pos.x + 0.5f * parent_size.x) -  0.5f * child_size.x;
		}

		if (valign == GuiVerticalAlignmentProperty::Top)
		{
			child_pos.y = (parent_pos.y + parent_size.y) - child_size.y;
		}
		else if (valign == GuiVerticalAlignmentProperty::Center)
		{
			child_pos.y = (parent_pos.y + 0.5f * parent_size.y) - 0.5f * child_size.y;
		}
		else if (valign == GuiVerticalAlignmentProperty::Bottom)
		{
			child_pos.y = parent_pos.y;
		}

		abstract_element->SetArrangedPosition(child_pos);
		abstract_element->SetArrangedSize(child_size);
	}
}
