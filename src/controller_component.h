#pragma once

#include <glm/glm.hpp>

#include "component.h"

namespace game
{
	class ControllerComponent : public core::Component
	{
		glm::vec2 velocity_;
		glm::vec2 position_;
		float rotation_;

	public:

		ControllerComponent(const glm::vec2 &position, const glm::vec2 &velocity,
			float rotation) :
			position_(position),
			velocity_(velocity),
			rotation_(rotation)
		{
		}

		virtual ~ControllerComponent() {}

		inline const glm::vec2 &GetVelocity() const { return velocity_; }

		inline void SetVelocity(const glm::vec2 &velocity) { velocity_ = velocity; }

		inline const glm::vec2 &GetPosition() const { return position_; }

		inline void SetPosition(const glm::vec2 &position) { position_ = position; }

		inline float GetRotation() const { return rotation_; }

		inline void SetRotation(float rotation) { rotation_ = rotation; }

	};
}
