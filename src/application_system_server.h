#pragma once

#include "application_types.h"

namespace core {

	class ApplicationSystemServer
	{
		const SystemsMap &map_;
		const SystemPtrs &ptrs_;

	public:

		ApplicationSystemServer(const SystemsMap &map, const SystemPtrs &ptrs) :
			map_(map), ptrs_(ptrs)
		{
		}

		~ApplicationSystemServer() = default;

		AudioCoreSystem &GetAudio() const
		{
			if (ptrs_.audio == nullptr)
			{
				Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_APPLICATION,
					"Failed to serve audio core system to application. Null valued.");
				SDL_assert(false);
			}

			return *ptrs_.audio;
		}

		GraphicsCoreSystem &GetGraphics() const
		{
			if (ptrs_.graphics == nullptr)
			{
				Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_APPLICATION,
					"Failed to serve graphics core system to application. Null valued.");
				SDL_assert(false);	
			}

			return *ptrs_.graphics;
		}

		InputCoreSystem &GetInput() const
		{
			if (ptrs_.input == nullptr)
			{
				Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_APPLICATION,
					"Failed to serve input core system to application. Null valued.");
				SDL_assert(false);
			}
			
			return *ptrs_.input;
		}

		EntityCoreSystem &GetEntity() const
		{
			if (ptrs_.entity == nullptr)
			{
				Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_APPLICATION,
					"Failed to serve entity core system to application. Null valued.");
				SDL_assert(false);
			}

			return *ptrs_.entity;
		}

		ResourceCoreSystem &GetResource() const
		{
			if (ptrs_.resource == nullptr)
			{
				Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_APPLICATION,
					"Failed to serve resource core system to application. Null valued.");
				SDL_assert(false);
			}

			return *ptrs_.resource;
		}

		GuiCoreSystem &GetGui() const
		{
			if (ptrs_.gui == nullptr)
			{
				Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_APPLICATION,
					"Failed to serve GUI core system to application. Null valued.");
				SDL_assert(false);
			}

			return *ptrs_.gui;
		}

		bool HasSystem(SystemFlagBit flag)
		{
			return map_.find(flag) != map_.cend();
		}
	};
}
