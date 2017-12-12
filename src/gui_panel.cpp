#include "gui_panel.h"

using namespace core;

GuiPanel::GuiPanel(const GuiContainer * const parent, GuiImage image) :
	GuiContainer(parent), image_(image)
{
}

GuiPanel::~GuiPanel()
{
}

void GuiPanel::SetPreferredSize(const glm::vec2 & preferred_size)
{
	preferred_size_ = preferred_size;
}

void GuiPanel::SetPreferredSizeRelative(const glm::vec2 & preferred_size)
{
	preferred_size_ = preferred_size;
}

GuiData GuiPanel::GetRenderData()
{

	GuiData data{};

	data.blend_hash = image_.GetBlendHash();
	data.texture_hash = image_.GetTextureHash();
	data.sampler_hash = image_.GetSamplerHash();

	data.color = glm::vec4(0.9f);

	data.sprite_transform = glm::mat4(1.0f);
	data.sprite_transform[0][0] = GetArrangedSize().x;
	data.sprite_transform[1][1] = GetArrangedSize().y;
	data.sprite_transform[3][0] = GetArrangedPosition().x;
	data.sprite_transform[3][1] = GetArrangedPosition().y;

	return data;
}

glm::vec2 GuiPanel::GetPreferredSize()
{
	glm::vec2 size = glm::vec2(image_.GetTextureWidth(), image_.GetTextureHeight());

	if (GetWidthProperty() == GuiSizeProperty::Absolute)
	{
		size.x = preferred_size_.x;
	} 

	if (GetHeightProperty() == GuiSizeProperty::Absolute)
	{
		size.y = preferred_size_.y;
	}

	return size;
}

glm::vec2 GuiPanel::GetPreferredSizeRelative()
{
	glm::vec2 size = glm::vec2(0.0f);

	if (GetWidthProperty() == GuiSizeProperty::Relative)
	{
		size.x = relative_size_.x;
	}

	if (GetHeightProperty() == GuiSizeProperty::Relative)
	{
		size.y = relative_size_.y;
	}

	return size;
}
