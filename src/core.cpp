#include "core.h"

#include "SDL.h"

#include "SDL_image.h"

using namespace core;

Core::Core()
{
}

Core::~Core()
{

}

void Core::StartUp(const Config &config)
{
	config_ = config;

	SDL_Init(SDL_INIT_EVERYTHING);

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	resource_system_ = std::make_unique<ResourceCoreSystem>();

	input_system_ = std::make_unique<InputCoreSystem>();

	audio_system_ = std::make_unique<AudioCoreSystem>();

	graphics_system_ = std::make_unique<GraphicsCoreSystem>();

	gui_system_ = std::make_unique<GuiCoreSystem>();

	entity_system_ = std::make_unique<EntityCoreSystem>();

	resource_system_->StartUp(config_);

	input_system_->StartUp(config_);

	audio_system_->StartUp(config_);

	graphics_system_->StartUp(config_);

	gui_system_->StartUp(config_);

	entity_system_->StartUp(config_);
}

void Core::CleanUp()
{
	resource_system_->CleanUp();

	input_system_->CleanUp();

	audio_system_->CleanUp();

	graphics_system_->CleanUp();

	gui_system_->CleanUp();

	entity_system_->CleanUp();

	IMG_Quit();

	SDL_Quit();
}

Core & core::Core::GetInstance()
{
	static Core instance;
	return instance;
}
