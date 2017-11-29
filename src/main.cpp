#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "audio_core_system.h"
#include "graphics_core_system.h"
#include "input_core_system.h"
#include "entity_core_system.h"
#include "gui_core_system.h"
#include "resource_core_system.h"

#include "audio_source.h"
#include "config.h"
#include "logger.h"
#include "timing.h"
#include "renderer.h"
#include "event.h"
#include "entity_manager.h"

#include "text_render_system.h"
#include "sprite_render_system.h"
#include "controller_system.h"

#include "map_parser.h"
#include "map_view.h"

Sint32 main(Sint32 argc, char * argv[])
{
	// Initialize
	auto config = std::make_unique<core::Config>();
	config->Load("assets/scripts/config.chai");

	auto resource_core = std::make_unique<core::ResourceCoreSystem>();
	auto graphics_core = std::make_unique<core::GraphicsCoreSystem>();
	auto input_core = std::make_unique<core::InputCoreSystem>();

	resource_core->StartUp(*config);
	graphics_core->StartUp(*config);
	input_core->StartUp(*config);

	auto renderer = std::make_unique<core::Renderer>(*resource_core, *graphics_core);
	auto entity_manager = std::make_unique<core::EntityManager>();

	// Setup scene
	{
		using namespace core;

		float aspect = graphics_core->GetAspectRatio();
		
		entity_manager->AddSystem(new SpriteRenderSystem(*resource_core));
		entity_manager->AddSystem(new ControllerSystem(*input_core));
		entity_manager->AddSystem(new TextRenderSystem(*resource_core));

		auto * text_entity = entity_manager->CreateEntity("text");
		auto * text_drawable = entity_manager->AddEntityComponent<TextComponent>(
			text_entity->id, "assets/fonts/arial/arial.ttf", 36, "abcdefghijklmnopqrstuvwxyz", 
			glm::vec2(24.0f), 
			glm::vec2(128.0f, 128.0f));

		game::MapParser map_parser;
		game::MapData map = map_parser.GetMapData("assets/maps/inn_2.json");
		game::MapView map_view(map, *graphics_core, *entity_manager);
		map_view.Initialize();

		auto * character_entity = entity_manager->CreateEntity("character");
		auto * character_sprite = entity_manager->AddEntityComponent<SpriteComponent>(
			character_entity->id,  
			"assets/textures/temp/smiley.png", 
			glm::vec4(1.0f),
			glm::scale(glm::vec3(0.1f, 0.1f * aspect, 1.0f)));
		character_sprite->SetLayer(0);

		auto * character_controller = entity_manager->AddEntityComponent<ControllerComponent>(
			character_entity->id, 
			glm::vec2(0, 0),  
			glm::vec2(0, 0),
			0.0f);

		auto * character_animation = entity_manager->AddEntityComponent<SpriteAnimationComponent>(
			character_entity->id, 
			"assets/textures/temp/player_topdown.png", 
			24, 11, 4, 0, 6);
	}

	size_t sound_hash;
	auto * sound = resource_core->GetSoundCache().
		GetBufferFromFile("assets/audio/temp/fairywoods.wav", &sound_hash);

	core::AudioSource source(sound);
	source.SetRepeating(true);
	source.SetGain(0.5f);
	source.Play();

	// Main loop 
	bool running = true;
	double previous_time = core::GetSeconds();
	while(running)
	{
		double current_time = core::GetSeconds();
		double frame_time = current_time - previous_time;
		previous_time = current_time;

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			{
				running = false;
			}

			input_core->UpdateCurrentInput(event);
		}

		auto * text_entity = entity_manager->GetEntityByName("text");
		if (text_entity)
		{
			auto * text_drawable = entity_manager->GetEntityComponent<core::TextComponent>(text_entity->id);
			if (text_drawable)
			{
				text_drawable->SetText("FPS: " + std::to_string(1.0 / frame_time));
			}
		}
		
		entity_manager->Update((float)frame_time);

		renderer->Invoke((float)frame_time);

		SDL_GL_SwapWindow(graphics_core->GetWindow());

		input_core->CarryCurrentInput();
	}

	resource_core->CleanUp();
	graphics_core->CleanUp();
	input_core->CleanUp();

	return 0;
}