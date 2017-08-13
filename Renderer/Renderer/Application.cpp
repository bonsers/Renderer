#include "Application.h"
#include "Display.h"

#include <iostream>

Application::Application()
	:	m_cube("Models\\cube.obj")
{
	m_entities[0].pos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_entities[0].color = glm::vec3(1.0f, 0.5f, 0.5f);
	m_entities[1].pos = glm::vec3(2.0f, 2.0f, -4.0f);
	m_entities[1].color = glm::vec3(0.5f, 0.5f, 1.0f);
	m_entities[2].pos = glm::vec3(-3.0f, -1.0f, -1.0f);
	m_entities[2].color = glm::vec3(0.5f, 1.0f, 0.5f);

	
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
	glm::vec3 objectColor = glm::vec3(0.6f, 0.6f, 0.6f); // default color
	shader.setVec3("objectColor", objectColor);
	// set lightColor
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader.setVec3("lightColor", lightColor);
}


void Application::draw(Shaders& shader, Model& model)
{
	//Model modelCube(m_v);
	Model modelCube(m_cube.m_buffer);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	// DRAW GRID
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	int min = -10;
	int max = 10;
	glBegin(GL_LINES);
	for (int i = min; i <= max; i++) {
		glVertex3f(i, 0, min);
		glVertex3f(i, 0, max);
		glVertex3f(min, 0, i);
		glVertex3f(max, 0, i);
	};
	glEnd();
	
	// DRAW ENTITIES

	model.bind();
	for (int i = 0; i < m_entities.size(); i++)
	{
		glm::mat4 model;
		model = glm::translate(model, m_entities[i].pos);
		shader.setMat4("modelMatrix", model);
		glm::vec3 objectColor = m_entities[i].color;
		shader.setVec3("objectColor", objectColor);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, modelCube.getIndicesCount());
	}
	model.unbind();

}


void Application::runMainGameLoop()
{
	Display display;
	display.init();

	glEnable(GL_DEPTH_TEST);

	Camera camera;
	// Create shader
	Shaders shader1("Shaders\\vertex.glsl", "Shaders\\fragment.glsl");

	/*for (int k = 0; k < m_cube.m_buffer.size(); k++)
	{
		std::cout << m_cube.m_buffer[k] << "\t";
		if ((k + 1) % 6 == 0)
			std::cout << "\n";
		else if ((k + 1) % 3 == 0)
			std::cout << "\t";
	}*/
	Model modelCube(m_cube.m_buffer);

	while (display.isOpen())
	{
		float currentFrame = m_clock.getElapsedTime().asSeconds();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;

		display.clear();
		display.update();
		
		display.handleEvents(camera);
		input(camera);
		update(camera, shader1);
		draw(shader1, modelCube);
	}
}