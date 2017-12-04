#pragma once

#include "sprite_data_message_queue.h"
#include "text_data_message_queue.h"

namespace core
{
	class DataBus
	{
		
		SpriteDataMessageQueue sprites_;

		TextDataMessageQueue texts_;

	public:

		DataBus() = default;

		~DataBus() = default;

		SpriteDataMessageQueue &GetSpriteQueue()
		{
			return sprites_;
		}

		TextDataMessageQueue &GetTextQueue()
		{
			return texts_;
		}
	};
}
