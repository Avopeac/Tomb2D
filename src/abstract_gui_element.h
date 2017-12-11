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

		glm::vec2 relative_position_;
		glm::vec2 relative_size_;

		GuiElementType type_;
		GuiSizeProperty width_property_;
		GuiSizeProperty height_property_;
		GuiHorizontalAlignmentProperty horizontal_alignment_;
		GuiVerticalAlignmentProperty vertical_alignment_;

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

		inline void SetVerticalAlignmentProperty(GuiVerticalAlignmentProperty alignment)
		{
			vertical_alignment_ = alignment;
		}

		inline GuiVerticalAlignmentProperty GetVerticalAlignmentProperty()
		{
			return vertical_alignment_;
		}

		inline void SetHorizontalAlignmentProperty(GuiHorizontalAlignmentProperty alignment)
		{
			horizontal_alignment_ = alignment;
		}

		inline GuiHorizontalAlignmentProperty GetHorizontalAlignmentProperty()
		{
			return horizontal_alignment_;
		}

		inline void SetWidthProperty(GuiSizeProperty width)
		{
			width_property_ = width;
		}

		inline GuiSizeProperty GetWidthProperty()
		{
			return width_property_;
		}

		inline void SetHeightProperty(GuiSizeProperty height)
		{
			height_property_ = height;
		}

		inline GuiSizeProperty SetHeightProperty()
		{
			return height_property_;
		}

		inline void SetInternalRelativeSize(const glm::vec2 &relative_size)
		{
			relative_size_ = relative_size;
		}

		inline void SetInternalRelativePosition(const glm::vec2 &relative_position)
		{
			relative_position_ = relative_position;
		}

		inline const glm::vec2 &GetInternalRelativeSize() const
		{
			return relative_size_;
		}

		inline const glm::vec2 &GetInternalRelativePosition() const
		{
			return relative_position_;
		}

		virtual GuiData GetRenderData() = 0;

		virtual glm::vec2 GetPreferredSize() = 0;
 	};
}
