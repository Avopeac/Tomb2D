#include "controller_system.h"

#include "glm/gtc/matrix_transform.hpp"

#include "entity_manager.h"
#include "core.h"
#include "data_pipe_hub.h"
#include "timing.h"

using namespace core;

void ControllerSystem::Initialize(Entity * entity)
{

	if (!entity)
	{
		return;
	}
}

void ControllerSystem::Update(Entity * entity, float delta_time)
{
	if (!entity)
	{
		return;
	}

	auto * controller_component = EntityManager::Get().GetEntityComponent<ControllerComponent>(entity->id);

	if (controller_component)
	{
		auto * input = core::Core::GetInputSystem();

		glm::vec2 velocity(0.0f);
		float rotation = 0.0f;
		
		if (input->KeyPressed(core::Key::KeyA)) { velocity.x -= 1.0f; }
		if (input->KeyPressed(core::Key::KeyD)) { velocity.x += 1.0f; }
		if (input->KeyPressed(core::Key::KeyW)) { velocity.y += 1.0f; }
		if (input->KeyPressed(core::Key::KeyS)) { velocity.y -= 1.0f; }

		float length = glm::length(velocity);
		if (length > 0.0f)
		{
			controller_component->SetVelocity(velocity / length);
		}
		else
		{
			controller_component->SetVelocity(glm::vec2(0.0f));
		}

		if (input->KeyPressed(core::Key::KeyQ)) { rotation -= 1.0f; }
		if (input->KeyPressed(core::Key::KeyE)) { rotation += 1.0f; }

		controller_component->SetRotation(rotation);

		glm::vec2 position = controller_component->GetVelocity() * delta_time;

		controller_component->SetPosition(position);
	}

	auto * sprite_component = EntityManager::Get().GetEntityComponent<SpriteComponent>(entity->id);

	if (sprite_component && controller_component)
	{
		glm::mat4 transform = sprite_component->GetTransform();
		transform *= glm::translate(glm::mat4(1.0f), glm::vec3(controller_component->GetPosition(), 0.0f));
		transform *= glm::rotate(glm::mat4(1.0f), glm::radians(controller_component->GetRotation()), glm::vec3(0, 0, 1));
		sprite_component->SetTransform(transform);
	}
}

void ControllerSystem::Clean(Entity * entity)
{
	// No need to clean anything for this system / component 
}