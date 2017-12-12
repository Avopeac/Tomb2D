#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gui_tree.h"
#include "gui_container.h"
#include "gui_panel.h"
#include "gui_icon.h"
#include "gui_table_layout.h"
#include "application_system_server.h"

using namespace core;

GuiTree::GuiTree(const ApplicationSystemServer &server,
	GuiDataMessageQueue &gui_queue) :
	server_(server), gui_queue_(gui_queue)
{
	GuiImage image(server_, "assets/textures/ui/vert_grad_gray.png", 
		BlendMode::SrcAlpha, BlendMode::OneMinusSrcAlpha,
		Wrapping::ClampToEdge, Wrapping::ClampToEdge, 
		MagnificationFiltering::Linear,
		MinificationFiltering::LinearMipmapLinear);

	GuiImage icon_image(server_, "assets/textures/ui/cursorSword_silver.png",
		BlendMode::SrcAlpha, BlendMode::OneMinusSrcAlpha,
		Wrapping::ClampToEdge, Wrapping::ClampToEdge,
		MagnificationFiltering::Linear,
		MinificationFiltering::LinearMipmapLinear);

	auto top_bar = std::make_shared<GuiPanel>(nullptr, image);
	top_bar->SetArrangedPosition(glm::vec2(0.0f, server_.GetGraphics().GetBackbufferHeight() - 32));
	top_bar->SetArrangedSize(glm::vec2(server_.GetGraphics().GetBackbufferWidth(), 32));
	top_bar->SetVisible(true);
	top_bar->SetLayout<GuiTableLayout>(3, 3, glm::vec2(0.1f / 3.0f), glm::vec2(1.0f / 3.0f));

	auto icon = top_bar->AddChildElement<GuiIcon>(icon_image);
	icon->SetVerticalAlignmentProperty(GuiVerticalAlignmentProperty::Center);
	icon->SetHorizontalAlignmentProperty(GuiHorizontalAlignmentProperty::Center);
	icon->SetWidthProperty(GuiSizeProperty::Fill);
	icon->SetHeightProperty(GuiSizeProperty::Fill);
	icon->SetVisible(true);

	top_containers_.push_back(top_bar);
}

GuiTree::~GuiTree()
{
}

void GuiTree::Update(float delta_time)
{
	for (auto it = top_containers_.begin(); it != top_containers_.end(); ++it)
	{
		auto * container = (*it).get();

		if (container && container->IsVisible())
		{
			container->Arrange();

			DrawElement(*it);

			for (auto it = container->GetChildElementBeginIterator();
				it != container->GetChildElementEndIterator(); ++it)
			{
				DrawElement(*it);
			}
		}
	}
}

void GuiTree::DrawElement(const std::shared_ptr<AbstractGuiElement>& element)
{
	if (element && element->IsVisible())
	{
		gui_queue_.Push(element->GetRenderData());

		if (element->GetType() == GuiElementType::Container)
		{
			auto * container = static_cast<GuiContainer*>(element.get());
			for (auto it = container->GetChildElementBeginIterator();
				it != container->GetChildElementEndIterator(); ++it)
			{
				DrawElement(*it);
			}
		}		
	}
}
