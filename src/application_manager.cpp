#include <SDL.h>

#include "application_manager.h"
#include "timing.h"
#include "logger.h"

using namespace core;

ApplicationManager::ApplicationManager(Application * application, uint8_t system_flag_bits) :
	system_flag_bits_(system_flag_bits),
	application_(application), 
	renderer_(nullptr)
{
	SDL_Init(0);
}

ApplicationManager::~ApplicationManager()
{
	SDL_Quit();
}

void ApplicationManager::StartUp(const std::string &config_path)
{

	config_.Load(config_path);

	if (system_flag_bits_ & static_cast<uint8_t>(SystemFlagBit::Audio))
	{
		systems_map_.insert({ SystemFlagBit::Audio, std::move(std::make_unique<AudioCoreSystem>()) });
		system_ptrs_.audio = static_cast<AudioCoreSystem*>(systems_map_[SystemFlagBit::Audio].get());
	}

	if (system_flag_bits_ & static_cast<uint8_t>(SystemFlagBit::Entity))
	{
		systems_map_.insert({ SystemFlagBit::Entity, std::move(std::make_unique<EntityCoreSystem>()) });
		system_ptrs_.entity = static_cast<EntityCoreSystem*>(systems_map_[SystemFlagBit::Entity].get());
	}

	if (system_flag_bits_ & static_cast<uint8_t>(SystemFlagBit::Graphics))
	{
		systems_map_.insert({ SystemFlagBit::Graphics, std::move(std::make_unique<GraphicsCoreSystem>()) });
		system_ptrs_.graphics = static_cast<GraphicsCoreSystem*>(systems_map_[SystemFlagBit::Graphics].get());
	}

	if (system_flag_bits_ & static_cast<uint8_t>(SystemFlagBit::Gui))
	{
		systems_map_.insert({ SystemFlagBit::Gui, std::move(std::make_unique<GuiCoreSystem>()) });
		system_ptrs_.gui = static_cast<GuiCoreSystem*>(systems_map_[SystemFlagBit::Gui].get());
	}

	if (system_flag_bits_ & static_cast<uint8_t>(SystemFlagBit::Input))
	{
		systems_map_.insert({ SystemFlagBit::Input, std::move(std::make_unique<InputCoreSystem>()) });
		system_ptrs_.input = static_cast<InputCoreSystem*>(systems_map_[SystemFlagBit::Input].get());
	}

	if (system_flag_bits_ & static_cast<uint8_t>(SystemFlagBit::Resource))
	{
		systems_map_.insert({ SystemFlagBit::Resource, std::move(std::make_unique<ResourceCoreSystem>()) });
		system_ptrs_.resource = static_cast<ResourceCoreSystem*>(systems_map_[SystemFlagBit::Resource].get());
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

	system_server_ = std::make_unique<ApplicationSystemServer>(systems_map_, system_ptrs_);

	if (!application_->StartUp(*system_server_, config_))
	{
		// TODO: Ability to return a reason for the failure
		Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_APPLICATION,
			"Game application start up failed.");

		SDL_assert(false);
	}
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

		//Log(SDL_LOG_PRIORITY_VERBOSE, SDL_LOG_CATEGORY_APPLICATION,
			//std::to_string(frame_time).c_str());

		bool requested_quit = false;

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			// These events trigger quit of application
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			{
				requested_quit = true;
			}

			// Update current input state
			if (system_ptrs_.input)
			{
				system_ptrs_.input->UpdateCurrentInput(event);
			}
			
		}

		// Update game logic, the changes here will ripple into the other systems
		running = application_->Run(*system_server_, config_, float(frame_time));

		if (requested_quit)
		{
			running = false;
		}

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
		if (system_ptrs_.graphics)
		{
			SDL_GL_SwapWindow(system_ptrs_.graphics->GetWindow());
		}

		// Save previous input states
		if (system_ptrs_.input)
		{
			system_ptrs_.input->CarryCurrentInput();
		}
	}


}

void ApplicationManager::CleanUp()
{

	if (!application_->CleanUp(*system_server_))
	{
		// TODO: Ability to see reason for error
		Log(SDL_LOG_PRIORITY_ERROR, SDL_LOG_CATEGORY_APPLICATION,
			"Game application failed to clean up.");
	}

	for (auto it = systems_map_.begin(); it != systems_map_.end(); ++it)
	{
		it->second->CleanUp();
	}
}