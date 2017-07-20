#pragma once

#include <SFML\Graphics.hpp>
#include <memory>

class Display
{
public:
	Display();
	~Display();
	void init();
	void close();
	void clear();
	void update();
	void checkForClose();
	bool isOpen();
	std::unique_ptr<sf::RenderWindow> window;	// std::unique_ptr?

private:
	const int width = 800;
	const int height = 600;
};

