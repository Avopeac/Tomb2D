#include "gui_panel.h"

using namespace core;

GuiPanel::GuiPanel(const GuiContainer * const parent) :
	GuiContainer(parent)
{
}

GuiPanel::~GuiPanel()
{
}

void GuiPanel::SetPreferredSize(const glm::vec2 & preferred_size)
{
	preferred_size_ = preferred_size;
}

void GuiPanel::SetPreferredSizeRelative(const glm::vec2 & preferred_size)
{
	preferred_size_ = preferred_size;
}

glm::vec2 GuiPanel::GetPreferredSize()
{
	return glm::vec2(10.0f, 10.0f);
}

glm::vec2 GuiPanel::GetPreferredSizeRelative()
{
	return glm::vec2(10.0f, 10.0f);
}
