#include "Shaders.h"
#include <fstream>
#include <sstream>
#include <iostream>


Shaders::Shaders(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexSourceCode;
	std::string fragmentSourceCode;
	std::ifstream vertexInFile(vertexPath);
	std::ifstream fragmentInFile(fragmentPath);

	//
	//

	if (!vertexInFile.is_open())
	{
		throw std::runtime_error("ERROR::SHADER::COULD NOT OPEN VERTEX SHADER");
	}
	std::stringstream vertexStream;
	vertexStream << vertexInFile.rdbuf();
	vertexSourceCode = vertexStream.str();

	if (!fragmentInFile.is_open())
	{
		throw std::runtime_error("ERROR::SHADER::COULD NOT OPEN FRAGMENT SHADER");
	}
	std::stringstream fragmentStream;
	fragmentStream << fragmentInFile.rdbuf();
	fragmentSourceCode = fragmentStream.str();

	const char* vertexShaderCode = vertexSourceCode.c_str();
	const char* fragmentShaderCode = fragmentSourceCode.c_str();

	// COMPILE	

	//auto vertex, fragment;
	int success;
	char infoLog[512];

	auto vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// SHADER PROGRAM

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	// print linking errors if any
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


Shaders::~Shaders()
{
}

void Shaders::use()
{
	glUseProgram(m_ID);
}

void Shaders::setMat4(const std::string &name, const glm::mat4 &mat)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shaders::setFloat(const std::string &name, float value)
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shaders::setVec3(const std::string &name, const glm::vec3 &value)
{
	glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}