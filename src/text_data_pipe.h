#pragma once

#include <vector>

#include "glm/glm.hpp"

namespace core {

	struct TextData
	{
		size_t font_hash;
		size_t blend_hash;
		size_t sampler_hash;
		glm::vec2 scale;
		glm::vec2 position;
		std::string text_string;
	};

	class TextDataPipe
	{

		std::vector<TextData> data_;

	public:

		TextDataPipe() {}

		~TextDataPipe() {}

		void Push(const TextData &sprite_data)
		{
			data_.push_back(sprite_data);
		}

		void Flush()
		{
			data_.clear();
		}

		inline const std::vector<TextData> &GetData() const { return data_; }
	};
}
