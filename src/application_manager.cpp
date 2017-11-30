#include <SDL.h>

#include "application_manager.h"
#include "timing.h"
#include "audio_core_system.h"
#include "entity_core_system.h"
#include "graphics_core_system.h"
#include "gui_core_system.h"
#include "input_core_system.h"
#include "resource_core_system.h"

using namespace core;

ApplicationManager::ApplicationManager(uint8_t system_flag_bits) :
	system_flag_bits_(system_flag_bits),
	renderer_(nullptr)
{
}

ApplicationManager::~ApplicationManager()
{
}

void ApplicationManager::StartUp(const std::string &config_path)
{

	config_.Load(config_path);

	if (system_flag_bits_ & static_cast<uint8_t>(SystemFlagBit::Audio))
	{
		systems_map_.insert({ SystemFlagBit::Audio, std::move(std::make_unique<AudioCoreSystem>()) });
	}

	if (system_flag_bits_ & static_cast<uint8_t>(SystemFlagBit::Entity))
	{
		systems_map_.insert({ SystemFlagBit::Entity, std::move(std::make_unique<EntityCoreSystem>()) });
	}

	if (system_flag_bits_ & static_cast<uint8_t>(SystemFlagBit::Graphics))
	{
		systems_map_.insert({ SystemFlagBit::Graphics, std::move(std::make_unique<GraphicsCoreSystem>()) });
	}

	if (system_flag_bits_ & static_cast<uint8_t>(SystemFlagBit::Gui))
	{
		systems_map_.insert({ SystemFlagBit::Gui, std::move(std::make_unique<GuiCoreSystem>()) });
	}

	if (system_flag_bits_ & static_cast<uint8_t>(SystemFlagBit::Input))
	{
		systems_map_.insert({ SystemFlagBit::Input, std::move(std::make_unique<InputCoreSystem>()) });
	}

	if (system_flag_bits_ & static_cast<uint8_t>(SystemFlagBit::Resource))
	{
		systems_map_.insert({ SystemFlagBit::Resource, std::move(std::make_unique<ResourceCoreSystem>()) });
	}

	for (auto it = systems_map_.begin(); it != systems_map_.end(); ++it)
	{
		it->second->StartUp(config_);
	}

	// If both resource and graphics systems are available, then request renderer
	if (system_flag_bits_ & static_cast<uint8_t>(SystemFlagBit::Resource | SystemFlagBit::Graphics))
	{
		ResourceCoreSystem * resource_core = static_cast<ResourceCoreSystem*>(systems_map_[SystemFlagBit::Resource].get());
		GraphicsCoreSystem * graphics_core = static_cast<GraphicsCoreSystem*>(systems_map_[SystemFlagBit::Graphics].get());
		renderer_ = std::make_unique<Renderer>(*resource_core, *graphics_core);
	}

	start_up_hook(systems_map_, config_);
}

void ApplicationManager::Run()
{
	bool running = true;
	double previous_time = core::GetSeconds();
	while (running)
	{
		double current_time = core::GetSeconds();
		double frame_time = current_time - previous_time;
		previous_time = current_time;

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			// These events trigger quit of application
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			{
				running = false;
			}

			// Update current input state
			if (systems_map_.find(SystemFlagBit::Input) != systems_map_.end())
			{
				InputCoreSystem * input = static_cast<InputCoreSystem *>(systems_map_[SystemFlagBit::Input].get());
				input->UpdateCurrentInput(event);
			}
			
		}

		// Update game logic, the changes here will ripple into the other systems
		running = run_hook_(systems_map_, config_, float(frame_time));

		// Update core systems based on the game logic
		for (auto it = systems_map_.begin(); it != systems_map_.end(); ++it)
		{
			it->second->Update(float(frame_time));
		}

		// Invoke the renderer at the end of the frame
		if (renderer_)
		{
			renderer_->Invoke(float(frame_time));
		}

		// Present image
		if (systems_map_.find(SystemFlagBit::Graphics) != systems_map_.end())
		{
			GraphicsCoreSystem * graphics = static_cast<GraphicsCoreSystem *>(systems_map_[SystemFlagBit::Graphics].get());
			SDL_GL_SwapWindow(graphics->GetWindow());
		}

		// Save previous input states
		if (systems_map_.find(SystemFlagBit::Input) != systems_map_.end())
		{
			InputCoreSystem * input = static_cast<InputCoreSystem *>(systems_map_[SystemFlagBit::Input].get());
			input->CarryCurrentInput();
		}
	}


}

void ApplicationManager::CleanUp()
{
	for (auto it = systems_map_.begin(); it != systems_map_.end(); ++it)
	{
		it->second->CleanUp();
	}
}

void ApplicationManager::SetStartUpHook(std::function<bool(const SystemsMap&, const Config&)> hook)
{
	start_up_hook = hook;
}

void ApplicationManager::SetRunHook(std::function<bool(const SystemsMap&, const Config&, float)> hook)
{
	run_hook_ = hook;
}
