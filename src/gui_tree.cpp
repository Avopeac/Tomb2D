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
	root_ = new GuiContainer();

	auto * root_container = static_cast<GuiContainer*>(root_);
	root_container->SetVisible(true);

	auto child_panel = root_container->AddChildElement<GuiPanel>();
	if (auto shared = child_panel.lock())
	{
		size_t texture_hash;
		server_.GetResource().GetTextureCache().GetFromFile("assets/textures/white2x2.png", texture_hash);
		shared->SetTextureHash(texture_hash);
		shared->SetSize(glm::vec2(512.0f));
		shared->SetVisible(true);
	}
	
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

		GuiData draw_data_{};

		server_.GetResource().GetBlendCache().GetFromParameters(
			BlendMode::SrcAlpha, BlendMode::DstAlpha, &draw_data_.blend_hash);
		server_.GetResource().GetSamplerCache().GetFromParameters(MagnificationFiltering::Linear,
			MinificationFiltering::LinearMipmapLinear, Wrapping::ClampToEdge, Wrapping::ClampToEdge, &draw_data_.sampler_hash);

	}
	
}