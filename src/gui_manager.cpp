#include "gui_canvas.h"

#include "gui_panel.h"

using namespace graphics;

GuiManager::GuiManager(const GraphicsBase &graphics_base) :
	graphics_base_(&graphics_base)
{
	glm::vec2 canvase_size = { graphics_base_->GetBackbufferWidth(),
		graphics_base_->GetBackbufferHeight() };

	root_ = new GuiPanel(canvase_size, "");
}

GuiManager::~GuiManager()
{
	if (root_)
	{
		delete root_;
	}
}

void GuiManager::Render()
{
	// TODO: Push GUI tree render data to an actual GUI renderer as with the other things
}

void GuiManager::Update(float delta_time)
{

}
