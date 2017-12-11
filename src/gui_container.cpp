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
	glm::vec2 parent_size = GetInternalRelativeSize();
	glm::vec2 parent_pos = GetInternalRelativePosition();

	for (auto it = children_.begin(); it != children_.end(); ++it)
	{

		AbstractGuiElement * abstract_element = (*it).get();

		glm::vec2 child_preferred_size = abstract_element->GetPreferredSize();
		glm::vec2 child_pos = glm::vec2(0.0f);
		glm::vec2 child_size = glm::vec2(0.0f);

		if (GetHorizontalAlignmentProperty() == GuiHorizontalAlignmentProperty::Left)
		{

		}
		else if (GetHorizontalAlignmentProperty() == GuiHorizontalAlignmentProperty::Right)
		{

		}
		else if (GetHorizontalAlignmentProperty() == GuiHorizontalAlignmentProperty::Center)
		{
			child_pos.x = (parent_pos.x + 0.5f * parent_size.x) -  0.5f * child_preferred_size.x;
			child_size.x = child_preferred_size.x;
		}

		if (GetVerticalAlignmentProperty() == GuiVerticalAlignmentProperty::Top)
		{
			child_pos.y = (parent_pos.y + parent_size.y) - child_preferred_size.y;
			child_size.y = child_preferred_size.y;
		}
		else if (GetVerticalAlignmentProperty() == GuiVerticalAlignmentProperty::Center)
		{

		}
		else if (GetVerticalAlignmentProperty() == GuiVerticalAlignmentProperty::Bottom)
		{

		}

		abstract_element->SetInternalRelativePosition(child_pos);
		abstract_element->SetInternalRelativeSize(child_size);
	}
}
