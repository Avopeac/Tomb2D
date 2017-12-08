#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "gui_enums.h"
#include "gui_data_message_queue.h"
#include "application_system_server.h"

namespace core {

	class AbstractGuiElement
	{

		static size_t uid_counter_;

		size_t uid_;

		bool visible_ = true;

		glm::vec2 size_;
		glm::vec2 position_;

		GuiElementType type_;

	public:

		AbstractGuiElement(GuiElementType type);

		virtual ~AbstractGuiElement() = default;

		AbstractGuiElement(const AbstractGuiElement &) = delete;

		AbstractGuiElement(AbstractGuiElement &&) = delete;

		AbstractGuiElement& operator=(const AbstractGuiElement &) = delete;

		AbstractGuiElement& operator=(AbstractGuiElement &&) = delete;
		
		inline GuiElementType GetType() const
		{
			return type_;
		}

		inline size_t GetUniqueId() const
		{
			return uid_;
		}

		inline bool IsVisible() const
		{
			return visible_;
		}

		inline void SetVisible(bool visible)
		{
			visible_ = visible;
		}

		inline const glm::vec2 &GetPreferredPosition() const
		{
			return position_;
		}

		inline void SetPreferredPosition(const glm::vec2 &position)
		{
			position_ = position;
		}

		inline const glm::vec2 &GetPreferredSize() const
		{
			return size_;
		}

		inline void SetPreferredSize(const glm::vec2 &size)
		{
			size_ = size;
		}

		virtual GuiData GetRenderData(const ApplicationSystemServer &server) = 0;

 	};
}
