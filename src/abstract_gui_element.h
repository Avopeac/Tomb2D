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

		glm::vec2 arranged_position_;
		glm::vec2 arranged_size_;

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

		virtual GuiData GetRenderData() = 0;

		virtual glm::vec2 GetPreferredSize() = 0;

		GuiVerticalAlignmentProperty GetVerticalAlignmentProperty() const;

		GuiHorizontalAlignmentProperty GetHorizontalAlignmentProperty() const;
		
		GuiSizeProperty GetWidthProperty() const;

		GuiSizeProperty GetHeightProperty() const;

		GuiElementType GetType() const;

		size_t GetUniqueId() const;

		bool IsVisible() const;

		const glm::vec2 &GetArrangedSize() const;

		const glm::vec2 &GetArrangedPosition() const;

		void SetVisible(bool visible);

		void SetHeightProperty(GuiSizeProperty height);

		void SetWidthProperty(GuiSizeProperty width);

		void SetVerticalAlignmentProperty(GuiVerticalAlignmentProperty alignment);

		void SetHorizontalAlignmentProperty(GuiHorizontalAlignmentProperty alignment);

		void SetArrangedSize(const glm::vec2 &arranged_size);
		
		void SetArrangedPosition(const glm::vec2 &arranged_position);
 	};
}
