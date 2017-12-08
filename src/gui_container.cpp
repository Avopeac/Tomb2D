#include "gui_container.h"

using namespace core;

GuiContainer::GuiContainer(const GuiContainer * const parent) :
	AbstractGuiElement(GuiElementType::Container), parent_(parent)
{
}

GuiContainer::~GuiContainer()
{
}
