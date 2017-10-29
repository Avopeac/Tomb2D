#include "main_camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "config.h"
#include "keymap.h"

using namespace graphics;

MainCamera::MainCamera(const std::string & name, 
	float aspect_ratio, float fov, 
	float near, float far,
	const glm::vec3 &eye,
	const glm::vec3 &forward,
	const glm::vec3 &up) :
	AbstractCamera(name),
	aspect_ratio_(aspect_ratio),
	fov_(fov),
	near_(near),
	far_(far),
	initial_eye_(eye),
	initial_forward_(forward),
	initial_up_(up)
{
}

MainCamera::~MainCamera()
{
}

void MainCamera::Update(float delta_time)
{
	using namespace input;
	auto &keymap = Keymap::Get();

	float look_speed = 0.05f;
	if (keymap.KeyPressed(Key::KeyUp)) { euler_angles_.y += look_speed * delta_time; }
	if (keymap.KeyPressed(Key::KeyDown)) { euler_angles_.y -= look_speed * delta_time; }
	if (keymap.KeyPressed(Key::KeyLeft)) { euler_angles_.x -= look_speed * delta_time; }
	if (keymap.KeyPressed(Key::KeyRight)) { euler_angles_.x += look_speed * delta_time; }

	glm::mat3 rotation = glm::mat3(glm::eulerAngleYXZ(
		glm::two_pi<float>() - glm::radians(1000.0f * euler_angles_.x),
		glm::two_pi<float>() - glm::radians(1000.0f * euler_angles_.y),
		glm::radians(euler_angles_.z)));
	
	glm::vec3 velocity{};

	glm::vec3 initial_right = glm::normalize(glm::cross(initial_forward_, initial_up_)); 
	 
	if (keymap.KeyPressed(Key::KeyW)) { velocity += initial_forward_; }
	if (keymap.KeyPressed(Key::KeyS)) {	velocity -= initial_forward_; }
	if (keymap.KeyPressed(Key::KeyA)) {	velocity -= initial_right; }
	if (keymap.KeyPressed(Key::KeyD)) {	velocity += initial_right; }
	if (keymap.KeyPressed(Key::KeyQ)) { velocity += initial_up_; }
	if (keymap.KeyPressed(Key::KeyE)) { velocity -= initial_up_; }

	forward_ = rotation * initial_forward_;
	up_ = rotation * initial_up_;

	if (glm::length(velocity) > 0.001f)
	{
		eye_ = eye_ + rotation * 10.0f * glm::normalize(velocity) * delta_time;
	}

	view_ = glm::lookAt(eye_, eye_ + forward_, up_);
	proj_ = glm::perspective(fov_, aspect_ratio_, near_, far_);
	view_proj_ = proj_ * view_;
	inv_view_ = glm::inverse(view_);
	inv_proj_ = glm::inverse(proj_);
	inv_view_proj_ = glm::inverse(view_proj_);
}

