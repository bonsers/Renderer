#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
public:
	Camera();
	~Camera();
	void input(float dt);

	float x = 0.0f;
	float radius = 10.0f;
	float camX = sin(x) * radius;
	float camZ = cos(x) * radius;
	float zoom = 45.0f;
	float movementSpeed = 1.5f;
	
};

