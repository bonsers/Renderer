#include "Display.h"
#include <GL\glew.h>
#include <iostream>


Display::Display()
{
}


Display::~Display()
{
}


void Display::init()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.majorVersion = 3;
	settings.minorVersion = 3;

	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "OpenGL", sf::Style::Close, settings);

	GLenum err = glewInit();
	//std::cout << err << std::endl;
	glViewport(0, 0, window->getSize().x, window->getSize().y);
}


void Display::close()
{
	window->close();
}


void Display::clear()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}


void Display::update()
{
	window->display();
}


void Display::checkForClose()
{
	sf::Event e;
	while (window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			close();
		}
	}
}


bool Display::isOpen()
{
	return window->isOpen();
}


void Display::checkForMouseWheel()
{
	sf::Event e;
	while (window->pollEvent(e))
	{
		if (e.type == sf::Event::MouseWheelScrolled)
		{
			std::cout << "Scroll wheel movement: " << e.mouseWheelScroll.delta << std::endl;
		}
	}
}