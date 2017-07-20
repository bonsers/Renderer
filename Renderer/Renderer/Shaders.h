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
	unsigned int m_ID;
	void use();
	void setMat4(const std::string &name, const glm::mat4 &mat);
	void setFloat(const std::string &name, float value);
	void setVec3(const std::string &name, const glm::vec3 &value);
private:
	//
};