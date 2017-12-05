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
	root_ = new GuiContainer();

	GuiDrawData draw_data;
	draw_data.size = glm::vec2(512.0f);
	draw_data.texture_name = "assets/textures/white2x2.png";

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
			auto draw_data = root_container->GetDrawData();
			draw_data.visible = !draw_data.visible;
			root_container->SetDrawData(draw_data);
		}

		auto draw_data = root_container->GetDrawData();
		if (draw_data.visible)
		{

			SpriteData data{};

			server_.GetResource().GetBlendCache().GetFromParameters(
				draw_data.src_blend, draw_data.dst_blend, &data.blend_hash);
			server_.GetResource().GetSamplerCache().GetFromParameters(
				draw_data.mag_filter, draw_data.min_filter,
				draw_data.s_wrapping, draw_data.t_wrapping, &data.sampler_hash);
			server_.GetResource().GetTextureCache().GetFromFile(draw_data.texture_name,
				true, &data.texture_hash);

			data.sprite_layer = 0;
			data.sprite_transform = glm::scale(glm::mat4(1.0f),
				glm::vec3(server_.GetGraphics().PixelsToScale(draw_data.size), 1.0f));
			data.sprite_color = glm::vec4(1.0f);

			sprite_.Push(data);
		}
	}

	

	
}