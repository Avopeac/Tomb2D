#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gui_tree.h"
#include "gui_container.h"
#include "gui_panel.h"
#include "application_system_server.h"

using namespace core;

GuiTree::GuiTree(const ApplicationSystemServer &server,
	GuiDataMessageQueue &gui_queue) :
	server_(server), gui_queue_(gui_queue)
{
	GuiImage image{};
	image.SetTexturePath("assets/textures/white2x2.png");
	image.SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });

	auto root = std::make_shared<GuiPanel>(nullptr, image);
	root->SetVisible(true);
	root->SetPreferredPosition(glm::vec2(0.0f));
	root->SetPreferredSize(glm::vec2(1280.0f, 720.0f));
	root_ = static_cast<std::shared_ptr<GuiContainer>>(root);

	image.SetTexturePath("assets/textures/white2x2.png");
	image.SetColor({ 1.0f, 0.0f, 1.0f, 1.0f });

	auto child_panel0 = root_->AddChildElement<GuiPanel>(image);
	child_panel0->SetPreferredSize(glm::vec2(512.0f));
	child_panel0->SetPreferredPosition(glm::vec2(128.0f));
	child_panel0->SetVisible(true);

	image.SetColor({ 0.0f, 1.0f, 1.0f, 1.0f });

	auto child_panel1 = root_->AddChildElement<GuiPanel>(image);
	child_panel1->SetPreferredSize(glm::vec2(1280.0f, 64.0f));
	child_panel1->SetPreferredPosition(glm::vec2(0.0f, 720.0f - 64.0f));
	child_panel1->SetVisible(true);

	image.SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	auto grandchild_panel0 = child_panel0->AddChildElement<GuiPanel>(image);
	grandchild_panel0->SetPreferredSize(glm::vec2(128.0f));
	grandchild_panel0->SetPreferredPosition(glm::vec2(128.0f));
	grandchild_panel0->SetVisible(true);
}

GuiTree::~GuiTree()
{
}

void GuiTree::Update(float delta_time)
{
	if (root_)
	{
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
		gui_queue_.Push(element->GetRenderData(server_));

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
