#include "text_render_system.h"

#include "entity_manager.h"
#include "core.h"
#include "data_pipe_hub.h"

using namespace core;

TextRenderSystem::TextRenderSystem(ResourceCoreSystem &resource_core) :
	resource_core_(resource_core)
{

}

TextRenderSystem::~TextRenderSystem()
{

}

void TextRenderSystem::Initialize(Entity * entity)
{

	if (!entity)
	{
		return;
	}

	auto * text_component = manager_->GetEntityComponent<TextComponent>(entity->id);
	
	if (text_component && text_component->IsDirty())
	{
		InitializeTextComponent(text_component);

		text_component->LowerDirty();
	}

}

void TextRenderSystem::Update(Entity * entity, float delta_time)
{
	if (!entity)
	{
		return;
	}

	auto * text_component = manager_->GetEntityComponent<TextComponent>(entity->id);

	if (text_component)
	{
		if (text_component->IsDirty())
		{
			InitializeTextComponent(text_component);

			text_component->LowerDirty();
		}

		auto &text_data_pipe = DataPipeHub::Get().GetTextDataPipe();

		TextData text_data;
		text_data.font_hash = text_component->GetFontHash();
		text_data.blend_hash = text_component->GetBlendHash();
		text_data.sampler_hash = text_component->GetSamplerHash();
		text_data.text_string = text_component->GetText();
		text_data.position = text_component->GetFontPosition();
		text_data.scale = text_component->GetFontScale();
		// Push data 
		text_data_pipe.Push(text_data);
	}
}

void TextRenderSystem::Clean(Entity * entity)
{
	// No need to clean anything for this system 
}

void TextRenderSystem::InitializeTextComponent(TextComponent* text_component)
{
	if (text_component)
	{
		size_t blend_hash, sampler_hash, font_hash;

		resource_core_.GetBlendCache().GetFromParameters(text_component->GetSrcBlend(), 
			text_component->GetDstBlend(), &blend_hash);

		resource_core_.GetFontCache().GetFromFile(text_component->GetFontPath(), 
			text_component->GetFontPointSize(), &font_hash);

		resource_core_.GetSamplerCache().GetFromParameters(text_component->GetMagFilter(), 
			text_component->GetMinFilter(), text_component->GetWrappingS(), text_component->GetWrappingT(), &sampler_hash);

		text_component->SetFontHash(font_hash);
		text_component->SetBlendHash(blend_hash);
		text_component->SetSamplerHash(sampler_hash);
	}
}
