#include "gui_container.h"

using namespace core;

GuiContainer::GuiContainer(const GuiContainer * const parent) :
	AbstractGuiElement(GuiElementType::Container), parent_(parent)
{
}

GuiContainer::~GuiContainer()
{
}

void GuiContainer::Arrange()
{
	glm::vec2 size_px = GetArrangedSize();
	glm::vec2 pos_px = GetArrangedPosition();

	for (size_t i = 0; i < children_.size(); ++i)
	{
		auto * element = children_[i].get();

		float pos_x = 0.0f;
		float pos_y = 0.0f;
		float size_x = element->GetPreferredSizeRelative().x * size_px.x;
		float size_y = element->GetPreferredSizeRelative().y * size_px.y;

		// TODO: Pivot points
		switch (element->GetHorizontalAnchorPoint())
		{
			case GuiHorizontalAnchorPoint::Center: { pos_x = pos_px.x + 0.5f * (size_px.x - size_x); } break;
			case GuiHorizontalAnchorPoint::Right: { pos_x = pos_px.x + size_px.x - size_x; } break;
			case GuiHorizontalAnchorPoint::Left: { pos_x = pos_px.x + 0.0f; } break;
			default: break;
		}

		switch (element->GetVerticalAnchorPoint())
		{
			case GuiVerticalAnchorPoint::Middle: { pos_y = pos_px.y + 0.5f * (size_px.y - size_y); } break;
			case GuiVerticalAnchorPoint::Top: { pos_y = pos_px.y + size_px.y - size_y; } break;
			case GuiVerticalAnchorPoint::Bottom: { pos_y = pos_px.y + 0.0f; } break;
			default: break;
		}

		if (element->GetOffsetElement() != nullptr)
		{
			auto offset_element = element->GetOffsetElement();

			switch (element->GetOffsetHorizontalAnchor())
			{
				case GuiHorizontalAnchorPoint::Left: { pos_x = offset_element->GetArrangedPosition().x - size_x; } break;
				case GuiHorizontalAnchorPoint::Center: { pos_x = offset_element->GetArrangedPosition().x; } break;
				case GuiHorizontalAnchorPoint::Right: { pos_x = offset_element->GetArrangedPosition().x + size_x; } break;
				default: break;
			}

			switch (element->GetOffsetVerticalAnchor())
			{
				case GuiVerticalAnchorPoint::Top: { pos_y = offset_element->GetArrangedPosition().y + size_x; } break;
				case GuiVerticalAnchorPoint::Middle: { pos_y = offset_element->GetArrangedPosition().y; } break;
				case GuiVerticalAnchorPoint::Bottom: { pos_y = offset_element->GetArrangedPosition().y - size_x; } break;
			}
		}

		element->SetArrangedSize({ size_x, size_y });
		element->SetArrangedPosition({ pos_x, pos_y });

		if (element->GetType() == GuiElementType::Container)
		{
			auto * container = static_cast<GuiContainer*>(element);

			container->Arrange();
		}
	}
}
