#pragma once

#include <string>
#include <vector>
#include <glm\glm.hpp>

class ObjLoader
{
public:
	ObjLoader(std::string path);
	~ObjLoader();
	std::vector<float> m_buffer;

private:
	struct interimFace
	{
		std::string x;
		std::string y;
		std::string z;
	};
	struct attribute
	{
		float v;
		float vt;
		float vn;
	};
	struct face
	{
		attribute x;
		attribute y;
		attribute z;
	};
	void loadFromFile(std::string path, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &textures, std::vector<glm::vec3> &normals, std::vector<interimFace> &interimFaces);
	void split(std::vector<glm::vec3> &vec, std::string buf, char delim);
	void splitFaces(std::vector<interimFace> &vec, std::string buf, char delim);
	void splitFacesFurther(std::vector<interimFace> &vec, std::vector<face> &newVec);
	std::vector<std::string> splitByToken(std::string str, char token);
	void constructBuffer(std::vector<face> &faces, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<float> &buffer);

};

