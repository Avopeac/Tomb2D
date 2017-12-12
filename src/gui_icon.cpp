#include "gui_icon.h"

using namespace core;

GuiIcon::GuiIcon(const GuiContainer * const parent, const GuiImage & image) :
	GuiLeaf(parent), image_(image)
{
}

GuiIcon::~GuiIcon()
{
}

GuiData GuiIcon::GetRenderData()
{
	GuiData data{};

	data.blend_hash = image_.GetBlendHash();
	data.texture_hash = image_.GetTextureHash();
	data.sampler_hash = image_.GetSamplerHash();

	data.color = glm::vec4(1.0f);

	data.sprite_transform[0][0] = GetArrangedSize().x;
	data.sprite_transform[1][1] = GetArrangedSize().y;
	data.sprite_transform[3][0] = GetArrangedPosition().x;
	data.sprite_transform[3][1] = GetArrangedPosition().y;

	return data;
}

glm::vec2 GuiIcon::GetPreferredSize()
{
	return glm::vec2(image_.GetTextureWidth(), image_.GetTextureHeight());
}

glm::vec2 GuiIcon::GetPreferredSizeRelative()
{
	return glm::vec2();
}
