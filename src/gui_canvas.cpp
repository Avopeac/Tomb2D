#include "gui_canvas.h"

using namespace core;

GuiCanvas::GuiCanvas(const ApplicationSystemServer &server) :
	GuiContainer(nullptr)
{
	SetInternalRelativePosition(glm::vec2(0.0f));
	SetInternalRelativeSize(glm::vec2(server.GetGraphics().GetBackbufferWidth(),
		server.GetGraphics().GetBackbufferHeight()));
}

GuiCanvas::~GuiCanvas()
{

}

GuiData GuiCanvas::GetRenderData()
{
	// Don't care, we don't render anything as the canvas but its elements
	return GuiData();
}

glm::vec2 GuiCanvas::GetPreferredSize()
{
	return GetInternalRelativeSize();
}
