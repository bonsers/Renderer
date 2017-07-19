#include "Camera.h"
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>


Camera::Camera()
{
}


Camera::~Camera()
{
}


void Camera::input(float dt)
{
	//
	// Rotate using LEFT and RIGHT keys
	//
	float v = movementSpeed * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		x = x - v;
		camX = sin(x) * radius;
		camZ = cos(x) * radius;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		x = x + v;
		camX = sin(x) * radius;
		camZ = cos(x) * radius;
	}
	//
	// Zoom in and out with + or -
	//
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		if (zoom > 45.0f)
			zoom = 45.0f;
		else if(zoom < 1.0f)
			zoom = 1.0f;
		else
			zoom -= 0.05f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		if (zoom > 45.0f)
			zoom = 45.0f;
		else if (zoom < 1.0f)
			zoom = 1.0f;
		else
			zoom += 0.05f;
	}
}

