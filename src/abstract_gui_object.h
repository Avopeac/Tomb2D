#pragma once

#include <vector>
#include <memory>

namespace graphics {
	
	class AbstractGuiObject
	{

	protected:

		std::shared_ptr<AbstractGuiObject> parent_;

		std::vector<std::shared_ptr<AbstractGuiObject>> children_;
		
		AbstractGuiObject() = default;

	public:
		
		virtual ~AbstractGuiObject() = default;

		virtual void Initialize() = 0;

		virtual void Draw() = 0;

		virtual void Destroy() = 0;
	};
}

