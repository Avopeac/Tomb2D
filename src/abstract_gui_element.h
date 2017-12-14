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
		bool has_arranged_size_ = false;
		bool has_arranged_position_ = false;

		glm::vec2 preferred_relative_size_;
		glm::vec2 arranged_size_;
		glm::vec2 arranged_position_;

		GuiElementType type_;
		GuiVerticalAnchorPoint vertical_anchor_;
		GuiHorizontalAnchorPoint horizontal_achor_;

		GuiVerticalAnchorPoint offset_vertical_anchor_;
		GuiHorizontalAnchorPoint offset_horizontal_anchor_;
		std::shared_ptr<AbstractGuiElement> offset_element_ = nullptr;

	public:

		AbstractGuiElement(GuiElementType type);

		virtual ~AbstractGuiElement() = default;

		AbstractGuiElement(const AbstractGuiElement &) = delete;

		AbstractGuiElement(AbstractGuiElement &&) = delete;

		AbstractGuiElement& operator=(const AbstractGuiElement &) = delete;

		AbstractGuiElement& operator=(AbstractGuiElement &&) = delete;

		void SetPreferredSizeRelative(const glm::vec2 &preferred_size);

		glm::vec2 GetPreferredSizeRelative();

		GuiElementType GetType() const;

		GuiVerticalAnchorPoint GetVerticalAnchorPoint() const;

		GuiHorizontalAnchorPoint GetHorizontalAnchorPoint() const;

		size_t GetUniqueId() const;

		bool IsVisible() const;

		bool IsArranged() const;

		const glm::vec2 &GetArrangedSize() const;

		const glm::vec2 &GetArrangedPosition() const;

		void SetVisible(bool visible);

		void SetVerticalAnchorPoint(GuiVerticalAnchorPoint anchor);

		void SetHorizontalAnchorPoint(GuiHorizontalAnchorPoint anchor);

		void SetArrangedSize(const glm::vec2 &arranged_size);
		
		void SetArrangedPosition(const glm::vec2 &arranged_position);

		void SetOffsetToElement(const std::shared_ptr<AbstractGuiElement> &offset_element,
			GuiVerticalAnchorPoint offset_vertical_anchor,
			GuiHorizontalAnchorPoint offset_horizontal_anchor);

		const std::shared_ptr<AbstractGuiElement> &GetOffsetElement() const;

		GuiVerticalAnchorPoint GetOffsetVerticalAnchor() const;

		GuiHorizontalAnchorPoint GetOffsetHorizontalAnchor() const;

 	};
}
