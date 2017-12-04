#pragma once

#include "system.h"
#include "text_component.h"
#include "application_system_server.h"

#include "resource_core_system.h"
#include "text_data_message_queue.h"

namespace game
{

	class TextRenderSystem : public core::System<TextRenderSystem, TextComponent>
	{

		const core::ApplicationSystemServer &application_system_server_;

	public:

		TextRenderSystem(const core::ApplicationSystemServer &application_system_server);

		virtual ~TextRenderSystem();

		// Inherited via System
		virtual void Initialize(core::Entity * entity) override;

		virtual void Update(core::Entity * entity, float delta_time) override;

		virtual void Clean(core::Entity * entity) override;

	private:

		void InitializeTextComponent(TextComponent * sprite_component);

	};
}
