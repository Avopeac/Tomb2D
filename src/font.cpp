#include "font.h"

#include <functional>

#include "logger.h"

using namespace core;

Font::Font()
{
}

Font::~Font()
{
}

void Font::Create(const std::string &path, uint32_t pt_size)
{

	font_ = TTF_OpenFont(path.c_str(), pt_size);

	if (!font_)
	{
		core::Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_INPUT,
			"Could not load the requested font.");
	}

	glyph_textures_.resize(CHAR_MAP_LENGTH);
	glyph_data_.resize(CHAR_MAP_LENGTH);

	glGenTextures((GLsizei)glyph_textures_.size(), glyph_textures_.data());

	SDL_Color fg_color{ 255, 255, 255, 255 };
	SDL_Color bg_color{ 0, 0, 0, 0 };

	//GLint alignment;
	//glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (size_t i = 0; i < CHAR_MAP_LENGTH; ++i)
	{
		SDL_Surface * surface = TTF_RenderGlyph_Shaded(font_, CHAR_MAP[i], fg_color, bg_color);
		if (!surface)
		{
			core::Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_INPUT,
				"Could not load the requested glyph from font.");
			continue;
		}

		glyph_index_map_[CHAR_MAP[i]] = i;

		TTF_GlyphMetrics(font_, CHAR_MAP[i], &glyph_data_[i].min_x,
			&glyph_data_[i].max_x, &glyph_data_[i].min_y, &glyph_data_[i].max_y, &glyph_data_[i].advance);

		glyph_data_[i].bitmap_width = surface->w;
		glyph_data_[i].bitmap_height = surface->h;

		glBindTexture(GL_TEXTURE_2D, glyph_textures_[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, surface->w, surface->h,
			0, GL_RED, GL_UNSIGNED_BYTE, surface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		SDL_FreeSurface(surface);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	// Add space to glyph map
	glyph_index_map_[' '] = CHAR_MAP_LENGTH;
	glyph_data_.push_back(Glyph());
	glyph_textures_.push_back(0);
	TTF_GlyphMetrics(font_, ' ',
		&glyph_data_[CHAR_MAP_LENGTH].min_x,
		&glyph_data_[CHAR_MAP_LENGTH].max_x,
		&glyph_data_[CHAR_MAP_LENGTH].min_y, 
		&glyph_data_[CHAR_MAP_LENGTH].max_y, 
		&glyph_data_[CHAR_MAP_LENGTH].advance);

	// Add new line to glyph map
	glyph_index_map_[' '] = CHAR_MAP_LENGTH + 1;
	glyph_data_.push_back(Glyph());
	glyph_textures_.push_back(0);

	//glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
}

float Font::GetKerningDistance(char first, char second)
{
	return (float)TTF_GetFontKerningSizeGlyphs(font_, first, second);
}

float Font::GetFontLineSkip()
{
	return float(TTF_FontLineSkip(font_));
}

float Font::GetFontAscent()
{
	return float(TTF_FontAscent(font_));
}

Glyph * Font::GetGlyph(char letter)
{
	return glyph_index_map_.find(letter) != glyph_index_map_.end() ?
		&glyph_data_[glyph_index_map_[letter]] : nullptr;
}

GLuint * Font::GetGlyphTexture(char letter)
{
	return (glyph_index_map_.find(letter) != glyph_index_map_.end()) ?
		&glyph_textures_[glyph_index_map_[letter]] : nullptr;
}

void Font::Free()
{
	TTF_CloseFont(font_);

	glDeleteTextures((GLsizei)glyph_textures_.size(), glyph_textures_.data());
}

FontCache::FontCache()
{
	if (TTF_Init() < 0)
	{
		Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_RENDER,
			"Could not initialize SDL TTF library.");
	}
}

FontCache::~FontCache()
{
	TTF_Quit();
}

Font * FontCache::GetFromFile(const std::string & path, uint32_t pt_size, size_t * hash)
{
	size_t path_hash = std::hash<std::string>{}(path);

	if (fonts_.find(path_hash) == fonts_.end())
	{

		auto font_ptr = std::make_unique<Font>();
		font_ptr->Create(path, pt_size);
		fonts_.insert({ path_hash, std::move(font_ptr) });
	}

	if (hash)
	{
		*hash = path_hash;
	}

	return fonts_[path_hash].get();
}

Font * FontCache::GetFromHash(size_t hash)
{
	return fonts_.find(hash) != fonts_.end() ?
		fonts_[hash].get() : nullptr;
}
