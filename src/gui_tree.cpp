#include "gui_tree.h"

#include "gui_container.h"

using namespace core;

GuiTree::GuiTree() 
{
	root_ = new GuiContainer(glm::vec2(512,512), "root");
}

GuiTree::~GuiTree()
{
	if (root_)
	{
		delete root_;
	}
}

void GuiTree::Update(float delta_time)
{
	// TODO: Propagate input events to all elements
}