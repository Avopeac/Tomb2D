#include "gui_panel.h"

using namespace core;

GuiPanel::GuiPanel(const GuiContainer * const parent, GuiImage image) :
	GuiContainer(parent), image_(image)
{
}

GuiPanel::~GuiPanel()
{
}

GuiData GuiPanel::GetRenderData()
{

	GuiData data{};

	data.blend_hash = image_.GetBlendHash();
	data.texture_hash = image_.GetTextureHash();
	data.sampler_hash = image_.GetSamplerHash();

	data.color = glm::vec4(0.9f);

	data.sprite_transform = glm::mat4(1.0f);
	data.sprite_transform[0][0] = GetInternalRelativeSize().x;
	data.sprite_transform[1][1] = GetInternalRelativeSize().y;
	data.sprite_transform[3][0] = GetInternalRelativePosition().x;
	data.sprite_transform[3][1] = GetInternalRelativePosition().y;

	return data;
}

glm::vec2 GuiPanel::GetPreferredSize()
{
	return glm::vec2(image_.GetTextureWidth(), image_.GetTextureHeight());
}
