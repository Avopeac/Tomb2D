#include "gui_container.h"

using namespace graphics;

GuiContainer::GuiContainer(const glm::vec2 & size, const std::string & texture_name) :
	texture_name_(texture_name)
{
	preferred_size_ = size;
}

GuiContainer::~GuiContainer()
{
}
