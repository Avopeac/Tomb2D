#include "gui_tree.h"

#include "gui_panel.h"

using namespace graphics;

GuiTree::GuiTree(const GraphicsBase &graphics_base) :
	graphics_base_(&graphics_base)
{
	glm::vec2 canvas_size = { graphics_base_->GetBackbufferWidth(),
		graphics_base_->GetBackbufferHeight() };

	root_ = new GuiPanel(canvas_size, "");
}

GuiTree::~GuiTree()
{
	if (root_)
	{
		delete root_;
	}
}

void GuiTree::Render()
{
	// TODO: Push GUI tree render data to an actual GUI renderer as with the other things
}

void GuiTree::Update(float delta_time)
{
	// TODO: Propagate input events to all elements
}

Interaction GuiTree::GetHitInteraction()
{
	return Interaction();
}

Interaction GuiTree::GetHoverInteraction()
{
	return Interaction();
}

Interaction GuiTree::GetDehoverInteraction()
{
	return Interaction();
}
