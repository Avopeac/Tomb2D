#pragma once

#include <unordered_map>
#include <memory>

#include "GL/glew.h"

#include "glm/glm.hpp"

#include "ft2build.h"
#include "freetype/freetype.h"
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

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

	class Font : public base::Disposable
	{

		FT_Face face_;

		std::vector<FT_Glyph> glyphs_;
		std::vector<GLuint> glyph_textures_;
		std::unordered_map<char, size_t> glyph_index_map_;

	public:

		Font(); 

		~Font();

		void Create(FT_Library * library, const std::string &path,
			uint32_t width, uint32_t height);

		glm::vec2 GetKerningDistance(char first, char second);

		glm::vec2 GetGlyphAdvance(char letter);

		GLuint * GetGlyphTexture(char letter);

		// Inherited via Disposable
		virtual void Free() override;

	};

	class FontCache
	{

		FT_Library library_;

		std::unordered_map<size_t, std::unique_ptr<Font>> fonts_;

	public:

		FontCache();

		~FontCache();

		Font * GetFromFile(const std::string &path, uint32_t width, uint32_t height, size_t * hash = nullptr);

		Font * GetFromHash(size_t hash);
	};
}
