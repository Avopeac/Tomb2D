#pragma once

#include <unordered_map>
#include <memory>

#include "GL/glew.h"

#include "glm/glm.hpp"

#include "SDL_ttf.h"

#include "disposable.h"

namespace graphics {

	constexpr size_t CHAR_MAP_LENGTH{ 88 };

	constexpr char CHAR_MAP[CHAR_MAP_LENGTH]{
		'A', 'a', 'B', 'b',
		'C', 'c', 'D', 'd',
		'E', 'e', 'F', 'f',
		'G', 'g', 'H', 'h',
		'I', 'i', 'J', 'j',
		'K', 'k', 'L', 'l',
		'M', 'm', 'N', 'n',
		'O', 'o', 'P', 'p',
		'Q', 'q', 'R', 'r',
		'S', 's', 'T', 't',
		'U', 'u', 'V', 'v',
		'W', 'w', 'X', 'x',
		'Y', 'y', 'Z', 'z',
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9', '!', '\"',
		'#', '%', '&', '/',
		'(', ')', '=', '?',
		'*', '\'', ',', ';',
		'.', ':', '-', '_',
		'<', '>', '[', ']',
		'{', '}', '\\', '|' };

	struct Glyph
	{
		int min_x;
		int max_x;
		int min_y;
		int max_y;
		int advance;
		int bitmap_width;
		int bitmap_height;
	};

	class Font : public base::Disposable
	{
		TTF_Font * font_;
		std::vector<GLuint> glyph_textures_;
		std::vector<Glyph> glyph_data_;
		std::unordered_map<char, size_t> glyph_index_map_;

	public:

		Font(); 

		~Font();

		void Create(const std::string &path, uint32_t pt_size);

		float GetKerningDistance(char first, char second);

		float GetFontLineSkip();

		float GetFontAscent();

		Glyph * GetGlyph(char letter);

		GLuint * GetGlyphTexture(char letter);

		// Inherited via Disposable
		virtual void Free() override;

	};

	class FontCache
	{

		std::unordered_map<size_t, std::unique_ptr<Font>> fonts_;

	public:

		FontCache();

		~FontCache();

		Font * GetFromFile(const std::string &path, uint32_t pt_size, size_t * hash = nullptr);

		Font * GetFromHash(size_t hash);
	};
}
