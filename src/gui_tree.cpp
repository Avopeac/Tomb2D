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

	width_px_ = server_.GetGraphics().GetBackbufferWidth();
	height_px_ = server_.GetGraphics().GetBackbufferHeight();

	auto top_bar = std::make_shared<GuiPanel>(nullptr);
	top_bar->SetPreferredSizeRelative({ 1.0f, 0.05f });
	top_bar->SetHorizontalAnchorPoint(GuiHorizontalAnchorPoint::Center);
	top_bar->SetVerticalAnchorPoint(GuiVerticalAnchorPoint::Top);
	
	auto image0 = top_bar->AddChildElement<GuiImage>(server_, "assets/textures/ui/vert_grad_gray.png",
		BlendMode::SrcAlpha, BlendMode::OneMinusSrcAlpha,
		Wrapping::ClampToEdge, Wrapping::ClampToEdge,
		MagnificationFiltering::Linear,
		MinificationFiltering::LinearMipmapLinear);

	auto image1 = top_bar->AddChildElement<GuiImage>(server_, "assets/textures/ui/cursorGauntlet_bronze.png",
		BlendMode::SrcAlpha, BlendMode::OneMinusSrcAlpha,
		Wrapping::ClampToEdge, Wrapping::ClampToEdge,
		MagnificationFiltering::Linear,
		MinificationFiltering::LinearMipmapLinear);

	auto image2 = top_bar->AddChildElement<GuiImage>(server_, "assets/textures/ui/cursorGauntlet_grey.png",
		BlendMode::SrcAlpha, BlendMode::OneMinusSrcAlpha,
		Wrapping::ClampToEdge, Wrapping::ClampToEdge,
		MagnificationFiltering::Linear,
		MinificationFiltering::LinearMipmapLinear);


	image0->SetPreferredSizeRelative({ 1.0f, 1.0f });
	image0->SetHorizontalAnchorPoint(GuiHorizontalAnchorPoint::Left);
	image0->SetVerticalAnchorPoint(GuiVerticalAnchorPoint::Middle);
	
	image1->SetPreferredSizeRelative({ 0.025f, 1.0f });
	image1->SetHorizontalAnchorPoint(GuiHorizontalAnchorPoint::Left);
	image1->SetVerticalAnchorPoint(GuiVerticalAnchorPoint::Middle);

	image2->SetPreferredSizeRelative({ 0.025f, 1.0f });
	image2->SetOffsetToElement(image1, GuiVerticalAnchorPoint::Middle, GuiHorizontalAnchorPoint::Right);
	
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

		Arrange(element);

		if (element->IsVisible())
		{
			DrawElement(*i);
		}
	}
}

void GuiTree::Arrange(AbstractGuiElement * const element)
{

	float pos_x = 0.0f;
	float pos_y = 0.0f;
	float size_x = element->GetPreferredSizeRelative().x * width_px_;
	float size_y = element->GetPreferredSizeRelative().y * height_px_;

	// TODO: Pivot points
	switch (element->GetHorizontalAnchorPoint())
	{
		case GuiHorizontalAnchorPoint::Center: { pos_x = 0.5 * (width_px_ - size_x); } break;
		case GuiHorizontalAnchorPoint::Right: { pos_x = width_px_ - size_x; } break;
		case GuiHorizontalAnchorPoint::Left: { pos_x = 0.0f; } break;
		default: break;
	}

	switch (element->GetVerticalAnchorPoint())
	{
		case GuiVerticalAnchorPoint::Middle: { pos_y = 0.5 * (height_px_ - size_y); } break;
		case GuiVerticalAnchorPoint::Top: { pos_y = height_px_ - size_y; } break;
		case GuiVerticalAnchorPoint::Bottom: { pos_y = 0.0f; } break;
		default: break;
	}

	element->SetArrangedSize({ size_x, size_y });
	element->SetArrangedPosition({ pos_x, pos_y });

	if (element->GetType() == GuiElementType::Container)
	{
		auto * container = static_cast<GuiContainer*>(element);

		container->Arrange();
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


