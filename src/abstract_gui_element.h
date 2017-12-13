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
		GuiVerticalAnchorPoint vertical_anchor_;
		GuiHorizontalAnchorPoint horizontal_achor_;

	public:

		AbstractGuiElement(GuiElementType type);

		virtual ~AbstractGuiElement() = default;

		AbstractGuiElement(const AbstractGuiElement &) = delete;

		AbstractGuiElement(AbstractGuiElement &&) = delete;

		AbstractGuiElement& operator=(const AbstractGuiElement &) = delete;

		AbstractGuiElement& operator=(AbstractGuiElement &&) = delete;

		virtual glm::vec2 GetPreferredSize() = 0;

		virtual glm::vec2 GetPreferredSizeRelative() = 0;

		GuiElementType GetType() const;

		GuiVerticalAnchorPoint GetVerticalAnchorPoint() const;

		GuiHorizontalAnchorPoint GetHorizontalAnchorPoint() const;

		size_t GetUniqueId() const;

		bool IsVisible() const;

		const glm::vec2 &GetArrangedSize() const;

		const glm::vec2 &GetArrangedPosition() const;

		void SetVisible(bool visible);
		
		void SetVerticalAnchorPoint(GuiVerticalAnchorPoint anchor);

		void SetHorizontalAnchorPoint(GuiHorizontalAnchorPoint anchor);

		void SetArrangedSize(const glm::vec2 &arranged_size);
		
		void SetArrangedPosition(const glm::vec2 &arranged_position);
 	};
}
