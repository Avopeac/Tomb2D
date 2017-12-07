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
	root_ = new GuiContainer(GuiElementTypes::Root);
	auto * root_container = static_cast<GuiContainer*>(root_);
	root_container->SetVisible(true);

	auto child_panel0 = root_container->AddChildElement<GuiPanel>();
	child_panel0->SetTexturePath("assets/textures/white2x2.png");
	child_panel0->SetSize(glm::vec2(512.0f));
	child_panel0->SetPosition(glm::vec2(128.0f));
	child_panel0->SetVisible(true);
	child_panel0->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	auto child_panel1 = root_container->AddChildElement<GuiPanel>();
	child_panel1->SetTexturePath("assets/textures/white2x2.png");
	child_panel1->SetSize(glm::vec2(1280.0f, 64.0f));
	child_panel1->SetPosition(glm::vec2(0.0f, 720.0f - 64.0f));
	child_panel1->SetVisible(true);
	child_panel1->SetColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	auto grandchild_panel0 = child_panel0->AddChildElement<GuiPanel>();
	grandchild_panel0->SetTexturePath("assets/textures/white2x2.png");
	grandchild_panel0->SetSize(glm::vec2(128.0f));
	grandchild_panel0->SetPosition(glm::vec2(128.0f));
	grandchild_panel0->SetVisible(true);
	grandchild_panel0->SetColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
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
	auto * root_container = static_cast<GuiContainer*>(root_);
	if (root_container)
	{
		for (auto it = root_container->GetChildElementBeginIterator();
			it != root_container->GetChildElementEndIterator(); ++it)
		{
			DrawElement(*it);
		}
	}
}

void GuiTree::DrawElement(const std::shared_ptr<AbstractGuiElement>& element)
{
	if (element && element->GetType() == GuiElementTypes::Panel)
	{
		auto * container = static_cast<GuiPanel*>(element.get());
		
		if (container->IsVisible())
		{
			GuiData draw_data_{};

			server_.GetResource().GetBlendCache().GetFromParameters(
				container->GetBlendModeSrc(),
				container->GetBlendModeDst(),
				&draw_data_.blend_hash);

			server_.GetResource().GetSamplerCache().GetFromParameters(
				container->GetMagFilter(),
				container->GetMinFilter(),
				container->GetWrappingS(),
				container->GetWrappingT(),
				&draw_data_.sampler_hash);

			server_.GetResource().GetTextureCache().GetFromFile(
				container->GetTexturePath(),
				true,
				&draw_data_.texture_hash);

			draw_data_.sprite_transform = glm::mat4(1.0f);
			draw_data_.sprite_transform[0][0] = container->GetSize().x;
			draw_data_.sprite_transform[1][1] = container->GetSize().y;
			draw_data_.sprite_transform[3][0] = container->GetPosition().x;
			draw_data_.sprite_transform[3][1] = container->GetPosition().y;

			draw_data_.color = container->GetColor();

			gui_queue_.Push(draw_data_);

			for (auto it = container->GetChildElementBeginIterator();
				it != container->GetChildElementEndIterator(); ++it)
			{
				DrawElement(*it);
			}
		}
	}
}
