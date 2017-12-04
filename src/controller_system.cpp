#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "controller_system.h"
#include "timing.h"

using namespace game;

ControllerSystem::ControllerSystem(const core::ApplicationSystemServer &application_system_server) :
	application_system_server_(application_system_server)
{

}

ControllerSystem::~ControllerSystem()
{

}

void ControllerSystem::Initialize(core::Entity * entity)
{

	if (!entity)
	{
		return;
	}
}

void ControllerSystem::Update(core::Entity * entity, float delta_time)
{
	if (!entity)
	{
		return;
	}

	auto * controller_component = manager_->GetEntityComponent<ControllerComponent>(entity->id);

	if (controller_component)
	{
		glm::vec2 velocity(0.0f);
		float rotation = 0.0f;
		
		if (application_system_server_.GetInput().KeyPressed(core::Key::KeyA)) { velocity.x -= 1.0f; }
		if (application_system_server_.GetInput().KeyPressed(core::Key::KeyD)) { velocity.x += 1.0f; }
		if (application_system_server_.GetInput().KeyPressed(core::Key::KeyW)) { velocity.y += 1.0f; }
		if (application_system_server_.GetInput().KeyPressed(core::Key::KeyS)) { velocity.y -= 1.0f; }

		float length = glm::length(velocity);
		if (length > 0.0f)
		{
			controller_component->SetVelocity(velocity / length);
		}
		else
		{
			controller_component->SetVelocity(glm::vec2(0.0f));
		}

		if (application_system_server_.GetInput().KeyPressed(core::Key::KeyQ)) { rotation -= 1.0f; }
		if (application_system_server_.GetInput().KeyPressed(core::Key::KeyE)) { rotation += 1.0f; }

		controller_component->SetRotation(rotation);

		glm::vec2 position = controller_component->GetVelocity() * delta_time;

		controller_component->SetPosition(position);
	}

	auto * sprite_component = manager_->GetEntityComponent<SpriteComponent>(entity->id);

	if (sprite_component && controller_component)
	{
		glm::mat4 transform = sprite_component->GetTransform();
		transform *= glm::translate(glm::mat4(1.0f), glm::vec3(controller_component->GetPosition(), 0.0f));
		transform *= glm::rotate(glm::mat4(1.0f), glm::radians(controller_component->GetRotation()), glm::vec3(0, 0, 1));
		sprite_component->SetTransform(transform);
	}
}

void ControllerSystem::Clean(core::Entity * entity)
{
	// No need to clean anything for this system / component 
}