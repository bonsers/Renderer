#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
public:
	Camera();
	~Camera();
	void input(float dt);
	void Camera::zoom(int scrollWheelDelta);
	float m_camX;
	float m_camZ;
	float m_zoom = 45.0f;

private:
	float m_x = 0.0f;
	float m_radius = 10.0f;
	float m_movementSpeed = 1.5f;

};