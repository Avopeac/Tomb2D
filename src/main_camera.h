#pragma once

#include "abstract_camera.h"

namespace graphics
{
	class MainCamera : public AbstractCamera
	{
		glm::vec3 euler_angles_;

		glm::vec3 initial_eye_;
		glm::vec3 initial_forward_;
		glm::vec3 initial_up_;

		glm::vec3 eye_;
		glm::vec3 forward_;
		glm::vec3 up_;

		float aspect_ratio_;
		float fov_;
		float near_, far_;

	public:

		MainCamera(const std::string &name, 
			float aspect_ratio, float fov,
			float near, float far,
			const glm::vec3 &eye,
			const glm::vec3 &forward,
			const glm::vec3 &up);

		~MainCamera();

		virtual void Update(float delta_time) override;

	};
}
