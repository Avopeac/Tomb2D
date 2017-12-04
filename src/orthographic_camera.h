#pragma once

#include "abstract_camera.h"

namespace core
{
	class OrthographicCamera : public AbstractCamera
	{
		glm::vec3 initial_eye_;
		glm::vec3 initial_forward_;
		glm::vec3 initial_up_;

		glm::vec3 eye_;
		glm::vec3 forward_;
		glm::vec3 up_;

		glm::vec3 volume_;

	public:

		OrthographicCamera(const std::string &name, glm::vec3 volume,
			const glm::vec3 &eye,
			const glm::vec3 &forward,
			const glm::vec3 &up);

		~OrthographicCamera();

		virtual void Update(float delta_time) override;

		bool Intersects(const glm::vec2 &lower_left, const glm::vec2 &upper_right);
	};
}
