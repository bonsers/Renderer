#pragma once
#include <vector>
#include <GL\glew.h>
class Model
{
public:
	Model(const std::vector<GLfloat>& vertexPositions, const std::vector<GLuint>& indices);
	Model(const std::vector<GLfloat>& vertexPositions);
	~Model();
	void bind();
	void unbind();
	GLuint getIndicesCount() const;
private:
	void addVBO(int dim, const std::vector<GLfloat>& data);
	void addEBO(const std::vector<GLuint>& indices);
	std::vector<GLuint> m_buffers;
	GLuint m_vao;
	GLuint m_vboCount = 0;
	GLuint m_indicesCount = 0;
};

