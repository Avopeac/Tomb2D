#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace core {

	class AbstractGuiElement
	{

		size_t uid_;

	protected:

		std::vector<std::weak_ptr<AbstractGuiElement>> children_;

	public:

		AbstractGuiElement(size_t uid);

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
