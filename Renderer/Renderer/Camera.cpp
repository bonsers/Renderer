#include "Camera.h"
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>


Camera::Camera()
{
	m_camX = sin(m_x) * m_radius;
	m_camZ = cos(m_x) * m_radius;
}


Camera::~Camera()
{
}


void Camera::input(float dt)
{
	//
	// Rotate camera around object using LEFT and RIGHT keys
	//
	float v = m_movementSpeed * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_x -= v;
		m_camX = sin(m_x) * m_radius;
		m_camZ = cos(m_x) * m_radius;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_x += v;
		m_camX = sin(m_x) * m_radius;
		m_camZ = cos(m_x) * m_radius;
	}
	//
	// Zoom in and out with + or -
	//
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		if (m_zoom > 45.0f)
			m_zoom = 45.0f;
		else if (m_zoom < 1.0f)
			m_zoom = 1.0f;
		else
			m_zoom -= 0.05f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		if (m_zoom > 45.0f)
			m_zoom = 45.0f;
		else if (m_zoom < 1.0f)
			m_zoom = 1.0f;
		else
			m_zoom += 0.05f;
	}



}
