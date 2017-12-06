#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "gui_data_message_queue.h"

namespace core {

	class AbstractGuiElement
	{

		static size_t uid_counter_;

		size_t uid_;

		bool visible_ = true;

	protected:

		GuiData gui_data_;

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

		inline bool IsVisible() const
		{
			return visible_;
		}

		inline void SetVisible(bool visible)
		{
			visible_ = visible;
		}

		inline const GuiData &GetDrawData()
		{
			return gui_data_;
		}

		inline void SetDrawData(const GuiData &data)
		{
			gui_data_ = data;
		}
 	};
}
