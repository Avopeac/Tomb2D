#include "gui_leaf.h"

using namespace core;

GuiLeaf::GuiLeaf(const GuiContainer * const parent) :
	AbstractGuiElement(GuiElementType::Leaf), parent_(parent)
{
}

GuiLeaf::~GuiLeaf()
{
}
