#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "sprite_data_message_queue.h"
#include "text_data_message_queue.h"

namespace core {

	class AbstractGuiElement
	{

		static size_t uid_counter_;

		size_t uid_;

	public:

		AbstractGuiElement();

		virtual ~AbstractGuiElement() = default;

		AbstractGuiElement(const AbstractGuiElement &) = delete;

		AbstractGuiElement(AbstractGuiElement &&) = delete;

		AbstractGuiElement& operator=(const AbstractGuiElement &) = delete;

		AbstractGuiElement& operator=(AbstractGuiElement &&) = delete;

		inline size_t GetUniqueId() const
		{
			return uid_;
		}
	};
}
