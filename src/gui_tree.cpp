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

	auto child_panel = root_container->AddChildElement<GuiPanel>();
	child_panel->SetTexturePath("assets/textures/white2x2.png");
	child_panel->SetSize(glm::vec2(512.0f));
	child_panel->SetPosition(glm::vec2(0.0f));
	child_panel->SetVisible(true);
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

	auto * root_container = static_cast<GuiContainer*>(root_);
	if (root_container)
	{		
		for (auto it = root_container->GetChildElementBeginIterator();
			it != root_container->GetChildElementEndIterator(); ++it)
		{
			if (it->get()->IsVisible())
			{
				GuiData draw_data_{};

				if (it->get()->GetType() == GuiElementTypes::Panel)
				{
					GuiPanel * panel = static_cast<GuiPanel*>(it->get());

					server_.GetResource().GetBlendCache().GetFromParameters(
						panel->GetBlendModeSrc(), 
						panel->GetBlendModeDst(),
						&draw_data_.blend_hash);

					server_.GetResource().GetSamplerCache().GetFromParameters(
						panel->GetMagFilter(),
						panel->GetMinFilter(),
						panel->GetWrappingS(),
						panel->GetWrappingT(),
						&draw_data_.sampler_hash);

					server_.GetResource().GetTextureCache().GetFromFile(
						panel->GetTexturePath(),
						true,
						&draw_data_.texture_hash);

					draw_data_.sprite_transform = glm::mat4(1.0f);
					draw_data_.sprite_transform[0][0] = panel->GetSize().x;
					draw_data_.sprite_transform[1][1] = panel->GetSize().y;
					draw_data_.sprite_transform[3][0] = panel->GetPosition().x;
					draw_data_.sprite_transform[3][1] = panel->GetPosition().y;

				}

				gui_queue_.Push(draw_data_);
			}
		}
	}
	
}