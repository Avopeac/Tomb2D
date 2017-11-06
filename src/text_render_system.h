#pragma once

#include "system.h"

#include "text_component.h"

namespace entity
{

	class TextRenderSystem : public System<TextRenderSystem, TextComponent>
	{

	public:

		TextRenderSystem() {}

		virtual ~TextRenderSystem() {}

		// Inherited via System
		virtual void Initialize(Entity * entity) override;

		virtual void Update(Entity * entity, float delta_time) override;

		virtual void Clean(Entity * entity) override;

	private:

		void InitializeTextComponent(TextComponent * sprite_component);

	};
}
