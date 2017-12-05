#pragma once

#include <type_traits>
#include <vector>

#include "abstract_gui_element.h"
#include "gui_draw_data.h"

namespace core {

	class GuiContainer : public AbstractGuiElement
	{
		std::vector<std::shared_ptr<AbstractGuiElement>> children_;

		GuiDrawData draw_data_;

	public:

		GuiContainer() = default; 

		virtual ~GuiContainer() = default;

		template <typename T, std::enable_if_t<std::is_base_of_v<AbstractGuiElement, T>>,
			typename ... Args> std::weak_ptr<T> AddChildElement(Args ... args)
		{
			children_.push_back(std::make_shared<T>(std::forward<Args>(args)));
			return children_.back();
		}

		const auto &GetChildElementBeginIterator() const
		{
			return children_.cbegin();
		}

		const auto &GetChildElementEndIterator() const
		{
			return children_.cend();
		}

		const GuiDrawData &GetDrawData() const
		{
			return draw_data_;
		}

		void SetDrawData(const GuiDrawData &draw_data)
		{
			draw_data_ = draw_data;
		}
	};
}
