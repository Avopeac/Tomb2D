#include "gui_panel.h"

using namespace core;

GuiPanel::GuiPanel() : GuiContainer(GuiElementTypes::Panel)
{
}

GuiPanel::~GuiPanel()
{
}

void GuiPanel::SetWrappingS(Wrapping wrapping)
{
	s_wrapping_ = wrapping;
}

Wrapping GuiPanel::GetWrappingS() const
{
	return s_wrapping_;
}

void GuiPanel::SetWrappingT(Wrapping wrapping)
{
	t_wrapping_ = wrapping;
}

Wrapping GuiPanel::GetWrappingT() const
{
	return t_wrapping_;
}

void GuiPanel::SetBlendModeSrc(BlendMode mode)
{
	src_blend_ = mode;
}

BlendMode GuiPanel::GetBlendModeSrc() const
{
	return src_blend_;
}

void GuiPanel::SetBlendModeDst(BlendMode mode)
{
	dst_blend_ = mode;
}

BlendMode GuiPanel::GetBlendModeDst() const
{
	return dst_blend_;
}

void GuiPanel::SetMagFilter(MagnificationFiltering filter)
{
	mag_filter_ = filter;
}

MagnificationFiltering GuiPanel::GetMagFilter() const
{
	return mag_filter_;
}

void GuiPanel::SetMinFilter(MinificationFiltering filter)
{
	min_filter_ = filter;
}

MinificationFiltering GuiPanel::GetMinFilter() const
{
	return min_filter_;
}

void GuiPanel::SetTexturePath(const std::string & texture_path)
{
	texture_path_ = texture_path;
}

const std::string & GuiPanel::GetTexturePath() const
{
	return texture_path_;
}

void GuiPanel::SetColor(const glm::vec4 & color)
{
	color_ = color;
}

const glm::vec4 & GuiPanel::GetColor() const
{
	return color_;
}
