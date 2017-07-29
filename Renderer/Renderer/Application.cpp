#include "Application.h"
#include "Display.h"

#include <iostream>

Application::Application()
	:	m_cube("Models\\cube.obj")
{
	
}


Application::~Application()
{
}


void Application::input(Camera& camera)
{
	camera.input(m_deltaTime);
}


void Application::update(Camera& camera, Shaders& shader)
{
	shader.use();

	glm::mat4 projection = glm::perspective(glm::radians(camera.m_zoom), (float)800 / (float)600, 0.1f, 100.0f);
	shader.setMat4("projectionMatrix", projection);

	glm::mat4 view;
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	view = glm::lookAt(	glm::vec3(camera.m_camX, 0.0f, camera.m_camZ),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("viewMatrix", view);
	// set time
	GLfloat time = m_clock.getElapsedTime().asSeconds();
	//std::cout << time << std::endl;
	shader.setFloat("time", time);
	// set objectColor
	glm::vec3 objectColor = glm::vec3(0.5f, 1.0f, 0.5f);
	shader.setVec3("objectColor", objectColor);
	// set lightColor
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader.setVec3("lightColor", lightColor);
}


void Application::draw(Shaders& shader)
{
	//Model modelCube(m_v);
	Model modelCube(m_cube.m_buffer);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	modelCube.bind();
	std::vector<glm::vec3> cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  2.0f, -4.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f)
	};
	for (int i = 0; i < 3; i++)
	{
		glm::mat4 model;
		model = glm::translate(model, cubePositions[i]);
		shader.setMat4("modelMatrix", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	modelCube.unbind();
}


void Application::runMainGameLoop()
{
	Display display;
	display.init();

	glEnable(GL_DEPTH_TEST);

	Camera camera;
	// Create shader
	//Shaders shader1("Shaders\\vertex.glsl", "Shaders\\fragment.glsl");
	Shaders shader1("Shaders\\vertexLighting.glsl", "Shaders\\fragmentLighting.glsl");

	/*for (int k = 0; k < m_cube.m_buffer.size(); k++)
	{
		std::cout << m_cube.m_buffer[k] << "\t";
		if ((k + 1) % 9 == 0)
			std::cout << "\n";
		else if ((k + 1) % 3 == 0)
			std::cout << "\t";
	}*/

	while (display.isOpen())
	{
		float currentFrame = m_clock.getElapsedTime().asSeconds();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;

		display.clear();
		display.update();

		input(camera);
		update(camera, shader1);
		draw(shader1);



		display.checkForClose();
	}
}