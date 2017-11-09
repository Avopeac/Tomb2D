#include "SDL.h"
#include "SDL_image.h"

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "keymap.h"
#include "graphics.h"
#include "logger.h"
#include "timing.h"
#include "renderer.h"
#include "entity_manager.h"

#include "text_render_system.h"
#include "sprite_render_system.h"
#include "controller_system.h"

Sint32 main(Sint32 argc, char * argv[])
{
	// Initialization
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);



	// Load config
	input::Config config;
	config.Load("assets/scripts/config.chai");

	// Create window and initialize graphics
	graphics::GraphicsBase graphics_base(config);
	graphics::Renderer renderer(&graphics_base);

	auto &entity_manager = entity::EntityManager::Get();

	// Setup scene
	{
		using namespace entity;

		float aspect = graphics_base.GetAspectRatio();
		
		entity_manager.AddSystem(new SpriteRenderSystem());
		entity_manager.AddSystem(new ControllerSystem());
		entity_manager.AddSystem(new TextRenderSystem());

		auto * text_entity = entity_manager.CreateEntity("text");
		auto * text_drawable = entity_manager.AddEntityComponent<TextComponent>(
			text_entity->id, "assets/fonts/arial/arial.ttf", 48, 48, "abcdefghijklmnopqrstuvwxyz", 
			glm::vec2(24.0f), 
			glm::vec2(128.0f, 128.0f));

		auto * backdrop_entity = entity_manager.CreateEntity("backdrop");
		auto * backdrop_sprite = entity_manager.AddEntityComponent<SpriteComponent>(
			backdrop_entity->id, 
			"assets/textures/temp/sand.png", 
			glm::vec4(1.0f), 
			glm::scale(glm::vec3(1.0f)));

		auto * character_entity = entity_manager.CreateEntity("character");
		auto * character_sprite = entity_manager.AddEntityComponent<SpriteComponent>(
			character_entity->id, 
			"assets/textures/temp/smiley.png", 
			glm::vec4(1.0f),
			glm::scale(glm::vec3(0.1f, 0.1f * aspect, 1.0f)));

		auto * character_controller = entity_manager.AddEntityComponent<ControllerComponent>(
			character_entity->id, 
			glm::vec2(0, 0), 
			glm::vec2(0, 0),
			0.0f);

		auto * character_animation = entity_manager.AddEntityComponent<SpriteAnimationComponent>(
			character_entity->id, 
			"assets/textures/temp/player_topdown.png", 
			24, 11, 4, 0, 6);
	}
	
	// Main loop 
	bool running = true;
	double previous_time = util::GetSeconds();
	while(running)
	{
		double current_time = util::GetSeconds();
		double frame_time = current_time - previous_time;
		previous_time = current_time;

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			{
				running = false;
			}

			input::Keymap::Get().UpdateCurrentInput(event);
		}

		auto * text_entity = entity_manager.GetEntityByName("text");
		if (text_entity)
		{
			auto * text_drawable = entity_manager.GetEntityComponent<entity::TextComponent>(text_entity->id);
			if (text_drawable)
			{
				text_drawable->SetText("FPS:\n" + std::to_string(1.0 / frame_time));
			}
		}
		
		entity_manager.Update((float)frame_time);

		renderer.Invoke((float)frame_time);

		SDL_GL_SwapWindow(graphics_base.GetWindow());

		input::Keymap::Get().CarryCurrentInput();
	}

	IMG_Quit();
	SDL_Quit();
	
	return 0;
}