#pragma once
#include <GL\glew.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <string>

class Shaders
{
public:
	Shaders(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shaders();
	unsigned int ID;
	void use();
	void setViewMatrix(const glm::mat4& mat);
	void setModelMatrix(const glm::mat4& mat);
	void setProjMatrix(const glm::mat4& mat);
	void setMat4(const std::string &name, const glm::mat4 &mat);
	void setFloat(const std::string &name, float value);
	void setVec3(const std::string &name, const glm::vec3 &value);
private:
	void getUniformLocations();
	GLuint m_locationViewMatrix = 0;
	GLuint m_locationModelMatrix = 0;
	GLuint m_locationProjMatrix = 0;
};

