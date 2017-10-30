#include "orthographic_camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "config.h"
#include "keymap.h"

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
	using namespace input;
	auto &keymap = Keymap::Get();

	glm::vec3 velocity{};

	glm::vec3 initial_right = glm::normalize(glm::cross(initial_forward_, initial_up_));

	if (keymap.KeyPressed(Key::KeyA)) { velocity -= initial_right; }
	if (keymap.KeyPressed(Key::KeyD)) { velocity += initial_right; }
	if (keymap.KeyPressed(Key::KeyQ)) { velocity += initial_up_; }
	if (keymap.KeyPressed(Key::KeyE)) { velocity -= initial_up_; }

	forward_ = initial_forward_;
	up_ = initial_up_;

	if (glm::length(velocity) > 0.001f)
	{
		eye_ = eye_ + 10.0f * glm::normalize(velocity) * delta_time;
	}

	view_ = glm::lookAt(eye_, eye_ + forward_, up_); 
	proj_ = glm::ortho(-volume_.x, volume_.x, -volume_.y, volume_.y, -volume_.z, volume_.z);

	view_proj_ = proj_ * view_;
	inv_view_ = glm::inverse(view_);
	inv_proj_ = glm::inverse(proj_); 
	inv_view_proj_ = glm::inverse(view_proj_);

}