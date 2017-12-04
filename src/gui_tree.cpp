#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gui_tree.h"
#include "gui_container.h"
#include "application_system_server.h"

using namespace core;

GuiTree::GuiTree(const ApplicationSystemServer &server, 
	SpriteDataMessageQueue &sprite, 
	TextDataMessageQueue &text) :
	server_(server), sprite_(sprite), text_(text)
{
	root_ = new GuiContainer(uid_counter_++, glm::vec2(512,512),
		"assets/textures/white2x2.png");
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

		if (server_.GetInput().KeyDown(Key::KeySpace))
		{
			root_container->SetVisible(!root_container->IsVisible());
		}

		if (root_container->IsVisible())
		{
			SpriteData data{};
			server_.GetResource().GetBlendCache().GetFromParameters(
				BlendMode::SrcAlpha, BlendMode::OneMinusSrcAlpha, &data.blend_hash);
			server_.GetResource().GetSamplerCache().GetFromParameters(
				MagnificationFiltering::Linear, MinificationFiltering::Linear,
				Wrapping::ClampToEdge, Wrapping::ClampToEdge, &data.sampler_hash);
			server_.GetResource().GetTextureCache().GetFromFile(root_container->GetTextureName(),
				true, &data.texture_hash);

			data.sprite_layer = 0;
			data.sprite_transform = glm::scale(glm::mat4(1.0f),
				glm::vec3(server_.GetGraphics().PixelsToScale(root_container->GetSize()), 1.0f));
			data.sprite_color = glm::vec4(1.0f);

			sprite_.Push(data);
		}
	}

	

	
}