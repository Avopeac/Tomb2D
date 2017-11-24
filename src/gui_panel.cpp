#include "gui_panel.h"

using namespace graphics;

GuiPanel::GuiPanel(const glm::vec2 & size, const std::string & texture_name) :
	texture_name_(texture_name)
{
	preferred_size_ = size;
}

GuiPanel::~GuiPanel()
{
}
