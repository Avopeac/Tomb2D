#include "gui_image.h"

using namespace core;

GuiImage::GuiImage(const ApplicationSystemServer &server, const std::string &texture_path,
	BlendMode src, BlendMode dst, Wrapping s, Wrapping t,
	MagnificationFiltering mag, MinificationFiltering min) :
	texture_path_(texture_path),
	src_blend_(src),
	dst_blend_(dst),
	s_wrapping_(s),
	t_wrapping_(t),
	mag_filter_(mag),
	min_filter_(min)
{
	server.GetResource().GetBlendCache().GetFromParameters(
		src_blend_,
		dst_blend_,
		&blend_hash_);

	server.GetResource().GetSamplerCache().GetFromParameters(
		mag_filter_,
		min_filter_,
		s_wrapping_,
		t_wrapping_,
		&sampler_hash_);

	auto * texture = server.GetResource().GetTextureCache().GetFromFile(
		texture_path,
		true,
		&texture_hash_);

	texture_width_ = texture->GetWidth();
	texture_height_ = texture->GetHeight();
}

size_t GuiImage::GetSamplerHash() const
{
	return sampler_hash_;
}

size_t GuiImage::GetBlendHash() const
{
	return blend_hash_;
}

size_t GuiImage::GetTextureHash() const
{
	return texture_hash_;
}


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

MagnificationFiltering GuiImage::GetMagFilter() const
{
	return mag_filter_;
}

MinificationFiltering GuiImage::GetMinFilter() const
{
	return min_filter_;
}

const std::string & GuiImage::GetTexturePath() const
{
	return texture_path_;
}

size_t GuiImage::GetTextureWidth() const
{
	return texture_width_;
}

size_t GuiImage::GetTextureHeight() const
{
	return texture_height_;
}
