#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gui_tree.h"
#include "gui_container.h"
#include "gui_panel.h"
#include "gui_canvas.h"
#include "application_system_server.h"

using namespace core;

GuiTree::GuiTree(const ApplicationSystemServer &server,
	GuiDataMessageQueue &gui_queue) :
	server_(server), gui_queue_(gui_queue)
{
	GuiImage image(server_, "assets/textures/white2x2.png", 
		BlendMode::SrcAlpha, BlendMode::OneMinusSrcAlpha,
		Wrapping::ClampToEdge, Wrapping::ClampToEdge, 
		MagnificationFiltering::Linear,
		MinificationFiltering::LinearMipmapLinear);

	auto root = std::make_shared<GuiCanvas>(server_);
	root->SetWidthProperty(GuiSizeProperty::Fill);
	root->SetHeightProperty(GuiSizeProperty::Fill);
	root->SetHorizontalAlignmentProperty(GuiHorizontalAlignmentProperty::Center);
	root->SetVerticalAlignmentProperty(GuiVerticalAlignmentProperty::Center);
	root->SetVisible(true);
	root_ = static_cast<std::shared_ptr<GuiContainer>>(root);

	auto child_panel1 = root_->AddChildElement<GuiPanel>(image);
	child_panel1->SetHorizontalAlignmentProperty(GuiHorizontalAlignmentProperty::Center);
	child_panel1->SetVerticalAlignmentProperty(GuiVerticalAlignmentProperty::Bottom);
	child_panel1->SetWidthProperty(GuiSizeProperty::Fill);
	child_panel1->SetHeightProperty(GuiSizeProperty::Absolute);
	child_panel1->SetPreferredSize(glm::vec2(0.0f, 32.0f));
	child_panel1->SetVisible(true);

	auto child_panel0 = root_->AddChildElement<GuiPanel>(image);
	child_panel0->SetHorizontalAlignmentProperty(GuiHorizontalAlignmentProperty::Center);
	child_panel0->SetVerticalAlignmentProperty(GuiVerticalAlignmentProperty::Top);
	child_panel0->SetWidthProperty(GuiSizeProperty::Fill);
	child_panel0->SetHeightProperty(GuiSizeProperty::Absolute);
	child_panel0->SetPreferredSize(glm::vec2(0.0, 32.0f));
	child_panel0->SetVisible(true);

	//auto child_panel1 = root_->AddChildElement<GuiPanel>(image);
	//child_panel1->SetWidthProperty(GuiSizeProperty::Fill);
	//child_panel1->SetHeightProperty(GuiSizeProperty::Absolute);
	//child_panel1->SetHorizontalAlignmentProperty(GuiAlignmentProperty::Left);
	//child_panel1->SetVisible(true);

	//auto grandchild_panel0 = child_panel0->AddChildElement<GuiPanel>(image);
	//grandchild_panel0->SetVisible(true);
}

GuiTree::~GuiTree()
{
}

void GuiTree::Update(float delta_time)
{
	if (root_)
	{
		root_->Arrange();

		for (auto it = root_->GetChildElementBeginIterator();
			it != root_->GetChildElementEndIterator(); ++it)
		{
			DrawElement(*it);
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
