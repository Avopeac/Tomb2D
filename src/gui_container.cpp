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

	if (layout_)
	{
		layout_->Arrange(children_, parent_pos, parent_size);
	}
}
