#include "orthographic_camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "config.h"
#include "core.h"

using namespace graphics;

OrthographicCamera::OrthographicCamera(const std::string & name, glm::vec3 volume,  
	const glm::vec3 & eye, 
	const glm::vec3 & forward, 
	const glm::vec3 & up) :
	AbstractCamera(name), 
	volume_(volume),
	eye_(eye),
	forward_(forward),
	up_(up),
	initial_eye_(eye),
	initial_forward_(forward),
	initial_up_(up)
{
}

OrthographicCamera::~OrthographicCamera()
{
}

void OrthographicCamera::Update(float delta_time)
{
	forward_ = initial_forward_;
	up_ = initial_up_;

	view_ = glm::lookAt(eye_, eye_ + forward_, up_); 
	proj_ = glm::ortho(-volume_.x, volume_.x, -volume_.y, volume_.y, -volume_.z, volume_.z);

	view_proj_ = proj_ * view_;
	inv_view_ = glm::inverse(view_);
	inv_proj_ = glm::inverse(proj_); 
	inv_view_proj_ = glm::inverse(view_proj_);

	auto * input = core::Core::GetInputSystem();

	glm::vec2 velocity{};
	
	if (input->KeyPressed(core::Key::KeyUp))
	{
		velocity.y += 1.0f;
	}

	if (input->KeyPressed(core::Key::KeyDown))
	{
		velocity.y -= 1.0f;
	}

	if (input->KeyPressed(core::Key::KeyLeft))
	{
		velocity.x -= 1.0f;
	}

	if (input->KeyPressed(core::Key::KeyRight))
	{
		velocity.x += 1.0f;
	}

	float len = glm::length(velocity);

	const float speed = 5.0f;

	if (len > glm::epsilon<float>())
	{
		glm::vec2 velocity_dir = velocity / len;
		eye_.x += speed * velocity_dir.x * delta_time;
		eye_.y += speed * velocity_dir.y * delta_time;
	}
}
