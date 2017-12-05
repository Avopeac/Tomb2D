#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "sample_game_application.h"
#include "sprite_render_system.h"
#include "controller_system.h"
#include "text_render_system.h"

#include "sprite_component.h"
#include "text_component.h"
#include "controller_component.h"

using namespace game;

bool SampleGameApplication::StartUp(const core::ApplicationSystemServer &server, const core::Config &config)
{

	float aspect = server.GetGraphics().GetAspectRatio();	
	server.GetEntity().AddSystem(new game::SpriteRenderSystem(server));
	server.GetEntity().AddSystem(new game::ControllerSystem(server));
	server.GetEntity().AddSystem(new game::TextRenderSystem(server));

	auto * text_entity = server.GetEntity().CreateEntity("text");
	auto * text_drawable = server.GetEntity().AddEntityComponent<game::TextComponent>(
	text_entity->id, "assets/fonts/arial/arial.ttf", 36, "abcdefghijklmnopqrstuvwxyz", 
	glm::vec2(24.0f), 
	glm::vec2(128.0f, 128.0f));

	map_parser_ = std::make_unique<MapParser>();
	map_data_ = std::make_unique<MapData>();
	*map_data_ = map_parser_->GetMapData("assets/maps/inn_2.json");
	map_view_ = std::make_unique<MapView>(*map_data_, server);
	map_view_->Initialize();

	auto * character_entity = server.GetEntity().CreateEntity("character");
	auto * character_sprite = server.GetEntity().AddEntityComponent<SpriteComponent>(
	character_entity->id,  
	"assets/textures/temp/smiley.png", 
	glm::vec4(1.0f),
	glm::scale(glm::vec3(0.1f, 0.1f * aspect, 1.0f)));
	character_sprite->SetLayer(0);

	auto * character_controller = server.GetEntity().AddEntityComponent<game::ControllerComponent>(
	character_entity->id, 
	glm::vec2(0, 0),  
	glm::vec2(0, 0),
	0.0f);

	auto * character_animation = server.GetEntity().AddEntityComponent<game::SpriteAnimationComponent>(
	character_entity->id, 
	"assets/textures/temp/player_topdown.png", 
	24, 11, 4, 0, 6);

	size_t sound_hash;
	auto * sound = server.GetResource().GetSoundCache().
		GetBufferFromFile("assets/audio/temp/fairywoods.wav", &sound_hash);

	background_music_ = server.GetAudio().CreateAudioSource(sound);
	background_music_->SetRepeating(true);
	background_music_->SetGain(1.0f);
	//background_music_->Play();

	return true;
}

bool SampleGameApplication::Run(const core::ApplicationSystemServer &server, const core::Config &config, float delta_time)
{
	++frame_counter_;
	average_frame_time += ((double)delta_time - average_frame_time) / frame_counter_;

	auto * text_entity = server.GetEntity().GetEntityByName("text");
	if (text_entity)
	{
		auto * text_drawable = server.GetEntity().GetEntityComponent<TextComponent>(text_entity->id);

		if (text_drawable)
		{
			text_drawable->SetText("FPS: " + std::to_string(1.0f / average_frame_time));
		}
	}

	return true;
}

bool SampleGameApplication::CleanUp(const core::ApplicationSystemServer &server)
{
	return true;
}