#include "gui_image.h"

using namespace core;

Wrapping GuiImage::GetWrappingS() const
{
	return s_wrapping_;
}

Wrapping GuiImage::GetWrappingT() const
{
	return t_wrapping_;
}

BlendMode GuiImage::GetBlendModeSrc() const
{
	return src_blend_;
}

BlendMode GuiImage::GetBlendModeDst() const
{
	return dst_blend_;
}

void GuiImage::SetBlendMode(BlendMode src, BlendMode dst)
{
	src_blend_ = src;
	dst_blend_ = dst;


}

MagnificationFiltering GuiImage::GetMagFilter() const
{
	return mag_filter_;
}

MinificationFiltering GuiImage::GetMinFilter() const
{
	return min_filter_;
}

void GuiImage::SetSampler(Wrapping s_wrapping, Wrapping t_wrapping, MagnificationFiltering magnification, MinificationFiltering minification)
{
}

void GuiImage::SetTexturePath(const std::string & texture_path)
{
	texture_path_ = texture_path;
}

const std::string & GuiImage::GetTexturePath() const
{
	return texture_path_;
}

void GuiImage::SetColor(const glm::vec4 & color)
{
	color_ = color;
}

const glm::vec4 & GuiImage::GetColor() const
{
	return color_;
}
