#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace core {

	class AbstractGuiElement
	{

		static size_t uid_counter_;

		size_t uid_;

	protected:

		std::vector<std::weak_ptr<AbstractGuiElement>> children_;

	public:

		AbstractGuiElement();

		~AbstractGuiElement() = default;

		AbstractGuiElement(const AbstractGuiElement &) = delete;

		AbstractGuiElement(AbstractGuiElement &&) = delete;

		AbstractGuiElement& operator=(const AbstractGuiElement &) = delete;

		AbstractGuiElement& operator=(AbstractGuiElement &&) = delete;

		inline size_t GetUniqueId() const
		{
			return uid_;
		}
	};
}
