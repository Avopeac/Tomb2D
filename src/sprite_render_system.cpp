#include "sprite_render_system.h"

#include "entity_manager.h"
#include "resource_manager.h"
#include "data_pipe_hub.h"

using namespace entity;

void SpriteRenderSystem::Initialize(Entity * entity)
{

	if (!entity)
	{
		return;
	}

	auto * component = EntityManager::Get().GetEntityComponent<SpriteComponent>(entity->id);
	if (component)
	{
		auto &blend_cache = graphics::ResourceManager::Get().GetBlendCache();
		auto &texture_cache = graphics::ResourceManager::Get().GetTextureCache();
		auto &sampler_cache = graphics::ResourceManager::Get().GetSamplerCache();
		
		blend_cache.GetFromParameters(component->src_blend_, component->dst_blend_, &component->blend_hash_);
		texture_cache.GetFromFile(component->texture_path_, true, &component->texture_hash_);
		sampler_cache.GetFromParameters(component->mag_filter_, component->min_filter_,
			component->s_wrapping_, component->t_wrapping_, &component->sampler_hash_);
	}

}

void SpriteRenderSystem::Update(Entity * entity)
{
	if (!entity)
	{
		return;
	}

	auto * component = EntityManager::Get().GetEntityComponent<SpriteComponent>(entity->id);
	if (component)
	{
		auto &sprite_data_pipe = graphics::DataPipeHub::Get().GetSpriteDataPipe();

		graphics::SpriteData sprite_data;
		sprite_data.blend_hash = component->blend_hash_;
		sprite_data.sampler_hash = component->sampler_hash_;
		sprite_data.texture_hash = component->texture_hash_;
		sprite_data.sprite_color = component->sprite_color_;
		sprite_data.sprite_layer = component->sprite_layer_;
		sprite_data.sprite_shape = component->sprite_shape_;
		sprite_data.sprite_transform = component->sprite_transform_;

		// Push data
		sprite_data_pipe.Push(sprite_data);
	}
}

void SpriteRenderSystem::Clean(Entity * entity)
{
	// No need to clean anything for this system / component 
}