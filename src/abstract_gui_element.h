#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "gui_data_message_queue.h"
#include "gui_element_types.h"

namespace core {

	class AbstractGuiElement
	{

		static size_t uid_counter_;

		size_t uid_;

		bool visible_ = true;

		GuiElementTypes type_;

	public:

		AbstractGuiElement(GuiElementTypes type);

		virtual ~AbstractGuiElement() = default;

		AbstractGuiElement(const AbstractGuiElement &) = delete;

		AbstractGuiElement(AbstractGuiElement &&) = delete;

		AbstractGuiElement& operator=(const AbstractGuiElement &) = delete;

		AbstractGuiElement& operator=(AbstractGuiElement &&) = delete;

		inline size_t GetUniqueId() const
		{
			return uid_;
		}

		inline GuiElementTypes GetType()
		{
			return type_;
		}

		inline bool IsVisible() const
		{
			return visible_;
		}

		inline void SetVisible(bool visible)
		{
			visible_ = visible;
		}
 	};
}
