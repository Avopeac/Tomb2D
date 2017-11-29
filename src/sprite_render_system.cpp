#include "sprite_render_system.h"

#include "entity_manager.h"
#include "core.h"
#include "data_pipe_hub.h"

using namespace core;

SpriteRenderSystem::SpriteRenderSystem(ResourceCoreSystem & resource_core) :
	resource_core_(resource_core)
{
}

SpriteRenderSystem::~SpriteRenderSystem()
{
}

void SpriteRenderSystem::Initialize(Entity * entity)
{

	if (!entity)
	{
		return;
	}

	auto * sprite_component = manager_->GetEntityComponent<SpriteComponent>(entity->id);
	auto * sprite_animation_component = manager_->GetEntityComponent<SpriteAnimationComponent>(entity->id);


	if (sprite_animation_component && sprite_animation_component->IsDirty())
	{
		InitializeSpriteAnimationComponent(sprite_animation_component);

		sprite_animation_component->LowerDirty();
	}

	if (sprite_component && sprite_component->IsDirty())
	{
		InitializeSpriteComponent(sprite_component);

		sprite_component->LowerDirty();
	}

}

void SpriteRenderSystem::Update(Entity * entity, float delta_time)
{
	if (!entity)
	{
		return;
	}

	auto * sprite_component = manager_->GetEntityComponent<SpriteComponent>(entity->id);
	auto * sprite_animation_component = manager_->GetEntityComponent<SpriteAnimationComponent>(entity->id);

	if (sprite_component)
	{
		if (sprite_animation_component && sprite_animation_component->IsDirty())
		{
			InitializeSpriteAnimationComponent(sprite_animation_component);

			sprite_animation_component->LowerDirty();
		}

		if (sprite_component->IsDirty())
		{
			InitializeSpriteComponent(sprite_component);

			sprite_component->LowerDirty();
		}
	
		auto &sprite_data_pipe = DataPipeHub::Get().GetSpriteDataPipe();

		SpriteData sprite_data;
		sprite_data.blend_hash = sprite_component->GetBlendHash();
		sprite_data.sampler_hash = sprite_component->GetSamplerHash();

		if (!sprite_animation_component)
		{
			sprite_data.texture_hash = sprite_component->GetTextureHash();
			sprite_data.sprite_animation = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);

		}
		else
		{
			sprite_data.texture_hash = sprite_animation_component->GetTextureHash();
			sprite_data.sprite_animation = glm::vec4(
				sprite_animation_component->GetNumRowFrames(),
				sprite_animation_component->GetNumColumnFrames(),
				sprite_animation_component->GetCurrentFrame(),
				0.0f);
		}
		
		sprite_data.sprite_color = sprite_component->GetColor();
		sprite_data.sprite_layer = sprite_component->GetLayer();
		sprite_data.sprite_shape = sprite_component->GetShape();
		sprite_data.sprite_transform = sprite_component->GetTransform();
		
		// Push data 
		sprite_data_pipe.Push(sprite_data);
	}

	if (sprite_animation_component)
	{ 

		float elapsed_time = sprite_animation_component->GetElapsedTime();

		if (elapsed_time > 1.0f / float(sprite_animation_component->GetFramesPerSecond()))
		{
			int32_t current = sprite_animation_component->GetCurrentFrame();
			if (current + 1 > sprite_animation_component->GetEndFrame()) 
			{
				// TODO: Conditional for loop animations
				sprite_animation_component->SetCurrentFrame(sprite_animation_component->GetStartFrame());
			}
			else
			{
				sprite_animation_component->SetCurrentFrame(current + 1);
			}

			sprite_animation_component->SetElapsedTime(0.0f);
		}
		else
		{
			sprite_animation_component->SetElapsedTime(elapsed_time + delta_time);
		}

		
	}
}

void SpriteRenderSystem::Clean(Entity * entity)
{
	// No need to clean anything for this system 
}

void SpriteRenderSystem::InitializeSpriteComponent(SpriteComponent * sprite_component)
{
	if (sprite_component)
	{
		size_t blend_hash, texture_hash, sampler_hash;

		resource_core_.GetBlendCache().GetFromParameters(sprite_component->GetSrcBlend(), 
			sprite_component->GetDstBlend(), &blend_hash);

		resource_core_.GetTextureCache().GetFromFile(sprite_component->GetTexturePath(), 
			true, &texture_hash);

		resource_core_.GetSamplerCache().GetFromParameters(sprite_component->GetMagFilter(), sprite_component->GetMinFilter(),
			sprite_component->GetWrappingS(), sprite_component->GetWrappingT(), &sampler_hash);

		sprite_component->SetTextureHash(texture_hash);
		sprite_component->SetBlendHash(blend_hash);
		sprite_component->SetSamplerHash(sampler_hash);
	}
}

void SpriteRenderSystem::InitializeSpriteAnimationComponent(SpriteAnimationComponent * sprite_animation_component)
{
	if (sprite_animation_component)
	{
		size_t texture_hash;

		resource_core_.GetTextureCache().GetFromFile(sprite_animation_component->GetTexturePath(),
			true, &texture_hash);

		sprite_animation_component->SetTextureHash(texture_hash);
	}
}
