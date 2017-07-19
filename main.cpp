#include "Application.h"
#include <iostream>

//#include <GL\glew.h>
//#include <SFML\Window.hpp>
//#include <glm\glm.hpp>



int main()
{
	std::cout << "HELLO CRUEL WORLD!" << std::endl;

	Application application;
	application.runMainGameLoop();


	return 0;
}