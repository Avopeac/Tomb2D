#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gui_tree.h"
#include "gui_container.h"
#include "gui_panel.h"
#include "gui_image.h"
#include "application_system_server.h"

using namespace core;

GuiTree::GuiTree(const ApplicationSystemServer &server,
	GuiDataMessageQueue &gui_queue) :
	server_(server), gui_queue_(gui_queue)
{

	auto top_bar = std::make_shared<GuiPanel>(nullptr);
	top_bar->SetArrangedPosition(glm::vec2(0.0f, server_.GetGraphics().GetBackbufferHeight() - 32));
	top_bar->SetArrangedSize(glm::vec2(server_.GetGraphics().GetBackbufferWidth(), 32));
	top_bar->SetVisible(true);


	auto image0 = top_bar->AddChildElement<GuiImage>(server_, "assets/textures/ui/vert_grad_gray.png",
		BlendMode::SrcAlpha, BlendMode::OneMinusSrcAlpha,
		Wrapping::ClampToEdge, Wrapping::ClampToEdge,
		MagnificationFiltering::Linear,
		MinificationFiltering::LinearMipmapLinear);

	image0->SetVisible(true);

	canvas_elements_.push_back(top_bar);
}

GuiTree::~GuiTree()
{
}

void GuiTree::Update(float delta_time)
{

	for (auto i = canvas_elements_.begin(); i!= canvas_elements_.end(); i++)
	{
		auto * element = (*i).get();

		if (element->IsVisible())
		{
			DrawElement(*i);
		}
	}
}

void GuiTree::DrawElement(const std::shared_ptr<AbstractGuiElement> &element)
{
	if (element->GetType() == GuiElementType::Leaf)
	{
		GuiLeaf * leaf = static_cast<GuiLeaf*>(element.get());

		gui_queue_.Push(leaf->GetRenderData());

	}
	else if (element->GetType() == GuiElementType::Container)
	{
		auto * container = static_cast<GuiContainer*>(element.get());
		for (auto it = container->GetChildElementBeginIterator();
			it != container->GetChildElementEndIterator(); ++it)
		{
			DrawElement(*it);
		}
	}
}


