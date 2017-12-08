#pragma once

#include <type_traits>
#include <vector>

#include "abstract_gui_element.h"

namespace core {

	class GuiContainer : public AbstractGuiElement
	{
		std::vector<std::shared_ptr<AbstractGuiElement>> children_;

		const GuiContainer * const parent_ = nullptr;

	public:

		GuiContainer(const GuiContainer * const parent);

		virtual ~GuiContainer();

		template <typename T, typename ... Args> std::shared_ptr<T> AddChildElement(Args &&... args)
		{
			static_assert(std::is_base_of<AbstractGuiElement, T>::value,
				"Derived class must be of base type AbstractGuiElement.");
			auto ptr = std::make_shared<T>(this, std::forward<Args>(args)...);
			children_.push_back(ptr);
			return ptr;
		}

		auto GetChildElementBeginIterator() const
		{
			return children_.cbegin();
		}

		auto GetChildElementEndIterator() const
		{
			return children_.cend();
		}
	};
}
