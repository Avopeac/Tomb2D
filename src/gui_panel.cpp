#include "gui_panel.h"

using namespace core;

GuiPanel::GuiPanel(const GuiContainer * const parent, GuiImage image) :
	GuiContainer(parent), image_(image)
{
}

GuiPanel::~GuiPanel()
{
}

GuiData GuiPanel::GetRenderData(const ApplicationSystemServer & server)
{

	GuiData data{};

	if (!initialized)
	{
		server.GetResource().GetBlendCache().GetFromParameters(
			image_.GetBlendModeSrc(),
			image_.GetBlendModeDst(),
			&blend_hash_);

		server.GetResource().GetSamplerCache().GetFromParameters(
			image_.GetMagFilter(),
			image_.GetMinFilter(),
			image_.GetWrappingS(),
			image_.GetWrappingT(),
			&sampler_hash_);

		server.GetResource().GetTextureCache().GetFromFile(
			image_.GetTexturePath(),
			true,
			&texture_hash_);

		initialized = true;
	}

	data.blend_hash = blend_hash_;
	data.texture_hash = texture_hash_;
	data.sampler_hash = sampler_hash_;

	data.color = image_.GetColor();

	data.sprite_transform = glm::mat4(1.0f);
	data.sprite_transform[0][0] = GetPreferredSize().x;
	data.sprite_transform[1][1] = GetPreferredSize().y;
	data.sprite_transform[3][0] = GetPreferredPosition().x;
	data.sprite_transform[3][1] = GetPreferredPosition().y;

	return data;
}
