#include "gui_container.h"

using namespace core;

GuiContainer::GuiContainer(size_t uid, const glm::vec2 & size, const std::string & texture_name) :
	AbstractGuiElement(uid), size_(size), texture_name_(texture_name)
{
}

GuiContainer::~GuiContainer()
{
}
