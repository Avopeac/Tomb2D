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

		glm::vec2 size_;

		glm::vec2 position_;

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

		inline const glm::vec2 &GetPosition() const
		{
			return position_;
		}

		inline void SetPosition(const glm::vec2 &position)
		{
			position_ = position;
		}

		inline const glm::vec2 &GetSize() const
		{
			return size_;
		}

		inline void SetSize(const glm::vec2 &size)
		{
			size_ = size;
		}
 	};
}
