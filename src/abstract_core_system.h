#pragma once

namespace core {

	class AbstractCoreSystem
	{
	public:

		AbstractCoreSystem() = default;

		~AbstractCoreSystem() = default;

		virtual void StartUp() = 0; 

		virtual void CleanUp() = 0;
	};
}