#pragma once

#include <type_traits>
#include <vector>

#include "abstract_gui_element.h"
#include "abstract_gui_layout.h"

namespace core {

	class GuiContainer : public AbstractGuiElement
	{
		std::vector<std::shared_ptr<AbstractGuiElement>> children_;

		std::shared_ptr<AbstractGuiLayout> layout_ = nullptr;

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

		template <typename T, typename ... Args> void SetLayout(Args &&... args)
		{
			static_assert(std::is_base_of<AbstractGuiLayout, T>::value,
				"Derived class must be of base type AbstractGuiLayout.");
			layout_ = std::make_shared<T>(std::forward<Args>(args)...);
		}

		auto GetChildElementBeginIterator() const
		{
			return children_.cbegin();
		}

		auto GetChildElementEndIterator() const
		{
			return children_.cend();
		}

		void Arrange();
	};
}
