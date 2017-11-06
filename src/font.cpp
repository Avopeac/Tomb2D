#include "font.h"

#include <functional>

#include "logger.h"

using namespace graphics;

Font::Font()
{

}

Font::~Font()
{
}

void Font::Create(FT_Library * library, const std::string &path, 
	uint32_t width, uint32_t height)
{
	if (FT_New_Face(*library, path.c_str(), 0, &face_))
	{
		debug::Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_INPUT,
			"Could not load the requested font.");
	}

	FT_Set_Char_Size(face_, width << 6, height << 6, 128, 128);

	glyphs_.resize(CHAR_MAP_LENGTH);
	glyph_textures_.resize(CHAR_MAP_LENGTH);
	glGenTextures(glyph_textures_.size(), glyph_textures_.data());
	
	GLint pack_alignment, unpack_alignment;
	glGetIntegerv(GL_PACK_ALIGNMENT, &pack_alignment);
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &unpack_alignment);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (size_t i = 0; i < CHAR_MAP_LENGTH; ++i)
	{

		glyph_index_map_[CHAR_MAP[i]] = i;

		if (FT_Load_Glyph(face_, FT_Get_Char_Index(face_, CHAR_MAP[i]), FT_LOAD_DEFAULT))
		{
			debug::Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_INPUT,
				"Could not load the requested glyph from font.");
		}
		
		if (FT_Get_Glyph(face_->glyph, &glyphs_[i]))
		{
			debug::Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_INPUT,
				"Could not get the requested glyph from font.");
		}

		FT_Glyph_To_Bitmap(&glyphs_[i], FT_Render_Mode::FT_RENDER_MODE_NORMAL, 0, 1);
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyphs_[i];
		FT_Bitmap bitmap = bitmap_glyph->bitmap;

		glBindTexture(GL_TEXTURE_2D, glyph_textures_[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bitmap.width, bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	}

	glBindTexture(GL_TEXTURE_2D, 0);

	glPixelStorei(GL_PACK_ALIGNMENT, pack_alignment);
	glPixelStorei(GL_UNPACK_ALIGNMENT, unpack_alignment);
}

glm::vec2 Font::GetKerningDistance(char first, char second)
{
	FT_Vector kerning_pair;
	FT_Get_Kerning(face_, FT_Get_Char_Index(face_, first), FT_Get_Char_Index(face_, second),
		FT_Kerning_Mode::FT_KERNING_DEFAULT, &kerning_pair);

	return glm::vec2(kerning_pair.x, kerning_pair.y);
}

glm::vec2 Font::GetGlyphAdvance(char letter)
{
	FT_Vector advance;
	if (glyph_index_map_.find(letter) != glyph_index_map_.end())
	{
		advance = glyphs_[glyph_index_map_[letter]]->advance;

		return glm::vec2(advance.x >> 6, advance.y >> 6);
	}

	return glm::vec2();
}

GLuint * Font::GetGlyphTexture(char letter)
{
	return (glyph_index_map_.find(letter) != glyph_index_map_.end()) ?
		&glyph_textures_[glyph_index_map_[letter]] : nullptr;
}

void Font::Free()
{
	for (auto & glyph : glyphs_)
	{
		FT_Done_Glyph(glyph);
	}

	FT_Done_Face(face_);

	glDeleteTextures(glyph_textures_.size(), glyph_textures_.data());
}

FontCache::FontCache()
{
	if (FT_Init_FreeType(&library_))
	{
		debug::Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_RENDER,
			"Could not initialize FreeType library.");
	}
}

FontCache::~FontCache()
{
	FT_Done_FreeType(library_);
}

Font * FontCache::GetFromFile(const std::string & path, uint32_t width, uint32_t height, size_t * hash)
{
	size_t path_hash = std::hash<std::string>{}(path);

	if (fonts_.find(path_hash) == fonts_.end())
	{

		auto font_ptr = std::make_unique<Font>();
		font_ptr->Create(&library_, path, width, height);
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
