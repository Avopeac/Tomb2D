#include "gui_tree.h"

#include "gui_container.h"

using namespace graphics;

GuiTree::GuiTree(const GraphicsBase &graphics_base) :
	graphics_base_(&graphics_base)
{
	glm::vec2 canvas_size = { graphics_base_->GetBackbufferWidth(),
		graphics_base_->GetBackbufferHeight() };

	root_ = new GuiContainer(canvas_size, "");
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

PropagateInteraction GuiTree::GetHitInteraction(const glm::vec2 & mouse)
{
	return PropagateInteraction();
}

PropagateInteraction GuiTree::GetHoverInteraction(const glm::vec2 & mouse)
{
	return PropagateInteraction();
}

PropagateInteraction GuiTree::GetDehoverInteraction(const glm::vec2 & mouse)
{
	return PropagateInteraction();
}