#pragma once

#include "system.h"
#include "text_component.h"
#include "resource_core_system.h"

namespace game
{

	class TextRenderSystem : public core::System<TextRenderSystem, TextComponent>
	{

		core::ResourceCoreSystem &resource_core_;

	public:

		TextRenderSystem(core::ResourceCoreSystem &resource_core);

		virtual ~TextRenderSystem();

		// Inherited via System
		virtual void Initialize(core::Entity * entity) override;

		virtual void Update(core::Entity * entity, float delta_time) override;

		virtual void Clean(core::Entity * entity) override;

	private:

		void InitializeTextComponent(TextComponent * sprite_component);

	};
}
