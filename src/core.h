#pragma once

#include <memory>

#include "core.h"

#include "config.h"

#include "abstract_core_system.h"

#include "audio_core_system.h"

#include "graphics_core_system.h"

#include "input_core_system.h"

#include "entity_core_system.h"

#include "gui_core_system.h"

#include "resource_core_system.h"

namespace core {

	class Core
	{

		std::unique_ptr<AudioCoreSystem> audio_system_ = nullptr;

		std::unique_ptr<GraphicsCoreSystem> graphics_system_ = nullptr;

		std::unique_ptr<InputCoreSystem> input_system_ = nullptr;

		std::unique_ptr<EntityCoreSystem> entity_system_ = nullptr;

		std::unique_ptr<GuiCoreSystem> gui_system_ = nullptr;

		std::unique_ptr<ResourceCoreSystem> resource_system_ = nullptr;

		Config config_;

	public:

		~Core();

		void StartUp(const Config &config);

		void CleanUp();

		static Core &GetInstance();

		static Config &GetConfig() { return GetInstance().config_; }

		static AudioCoreSystem * const GetAudioSystem() { return GetInstance().audio_system_.get(); }

		static GraphicsCoreSystem * const GetGraphicsSystem() { return GetInstance().graphics_system_.get(); }

		static InputCoreSystem * const GetInputSystem() { return GetInstance().input_system_.get(); }

		static EntityCoreSystem * const GetEntitySystem() { return GetInstance().entity_system_.get(); }

		static GuiCoreSystem * const GetGuiSystem() { return GetInstance().gui_system_.get(); }

		static ResourceCoreSystem * const GetResourceSystem() { return GetInstance().resource_system_.get(); }

	private:

		Core();

	};
}
