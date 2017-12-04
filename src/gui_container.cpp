#include "gui_container.h"

using namespace core;

GuiContainer::GuiContainer(const glm::vec2 & size, const std::string & texture_name) :
	size_(size), texture_name_(texture_name)
{
}

GuiContainer::~GuiContainer()
{
}
