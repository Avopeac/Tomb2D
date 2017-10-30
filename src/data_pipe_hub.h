#pragma once

#include "sprite_data_pipe.h"

namespace graphics
{
	class DataPipeHub
	{

		SpriteDataPipe sprite_data_pipe_;

	public:

		static DataPipeHub &Get()
		{
			static DataPipeHub instance;
			return instance;
		}

		~DataPipeHub() {}

		inline SpriteDataPipe &GetSpriteDataPipe() { return sprite_data_pipe_; }

	private:

		DataPipeHub() {}
	};
}