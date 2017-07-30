#include "ObjLoader.h"
#include <fstream>
#include <sstream>


ObjLoader::ObjLoader(std::string path)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> textures;
	std::vector<interimFace> interimFaces;
	loadFromFile(path, vertices, textures, normals, interimFaces);

	std::vector<face> newVec;
	newVec.resize(interimFaces.size());
	splitFacesFurther(interimFaces, newVec);

	//std::vector<float> m_buffer;
	constructBuffer(newVec, vertices, normals, m_buffer);
}


ObjLoader::~ObjLoader()
{
}


void ObjLoader::loadFromFile(std::string path, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &textures, std::vector<glm::vec3> &normals, std::vector<interimFace> &interimFaces)
{
	std::ifstream inFile(path);

	if (!inFile.is_open())
	{
		throw std::runtime_error("Error opening .obj file");
	}

	std::stringstream ss;

	std::string buf;
	while (std::getline(inFile, buf))
	{
		//std::cout << buf << std::endl;
		if (buf[0] == 'v')
		{
			if (buf[1] == ' ')
			{
				//std::cout << "vertex: " << buf << std::endl;
				split(vertices, buf, ' ');
			}
			else if (buf[1] == 't')
			{
				//split(textures, buf, ' ');
				//std::cout << "texture: " << buf << std::endl;
			}
			else if (buf[1] == 'n')
			{
				split(normals, buf, ' ');
				//std::cout << "normal: " << buf << std::endl;
			}
		}
		else if (buf[0] == 'f')
		{
			if (buf[1] == ' ')
				splitFaces(interimFaces, buf, ' ');
			//std::cout << "face: " << buf << std::endl;
		}
	}
}


void ObjLoader::split(std::vector<glm::vec3> &vec, std::string buf, char delim) // need whitespace as delim
{
	std::stringstream ss;
	ss.str(buf);
	std::string elem;
	int i = 0;
	GLfloat x, y, z;
	while (std::getline(ss, elem, delim))
	{
		if (elem == "v")
			continue;
		else if (elem == "vt")
			continue;
		else if (elem == "vn")
			continue;
		else if (elem == "f")
			continue;
		else
		{
			if (i == 0)
				x = std::stof(elem);
			if (i == 1)
				y = std::stof(elem);
			if (i == 2)
				z = std::stof(elem);
		}
		i++;
	}
	vec.push_back(glm::vec3(x, y, z));
}


void ObjLoader::splitFaces(std::vector<interimFace> &vec, std::string buf, char delim)
{
	std::stringstream ss;
	ss.str(buf);
	std::string elem;
	int i = 0;
	std::string x, y, z;
	while (std::getline(ss, elem, delim))
	{
		if (elem == "f")
			continue;
		else
		{
			if (i == 0)
				x = elem;
			if (i == 1)
				y = elem;
			if (i == 2)
				z = elem;
		}
		i++;
	}
	interimFace f;
	f.x = x;
	f.y = y;
	f.z = z;
	vec.push_back(f);
}


void ObjLoader::splitFacesFurther(std::vector<interimFace> &vec, std::vector<face> &newVec)
{
	std::vector<std::string> tempVec;
	for (int i = 0; i < vec.size(); i++)
	{
		tempVec = splitByToken(vec[i].x, '/');
		newVec[i].x.v = std::atof(tempVec[0].c_str());
		newVec[i].x.vt = std::atof(tempVec[1].c_str());
		newVec[i].x.vn = std::atof(tempVec[2].c_str());

		tempVec = splitByToken(vec[i].y, '/');
		newVec[i].y.v = std::atof(tempVec[0].c_str());
		newVec[i].y.vt = std::atof(tempVec[1].c_str());
		newVec[i].y.vn = std::atof(tempVec[2].c_str());

		tempVec = splitByToken(vec[i].z, '/');
		newVec[i].z.v = std::atof(tempVec[0].c_str());
		newVec[i].z.vt = std::atof(tempVec[1].c_str());
		newVec[i].z.vn = std::atof(tempVec[2].c_str());
	}
}


std::vector<std::string> ObjLoader::splitByToken(std::string str, char token)
{
	std::vector<std::string> result;
	int i = 0;
	int begin = 0;
	int size = 0;

	while (i < str.size())
	{
		if (str[i] == token)
		{
			result.push_back(str.substr(begin, size));
			begin = i + 1;
			size = 0;
		}
		else if (i == str.size() - 1)
		{
			result.push_back(str.substr(begin, size + 1));
		}
		else
		{
			size++;
		}
		i++;
	}

	for (int j = 0; j < result.size(); j++)
	{
		if (result[j] == "")
			result[j] = "-1";
	}
	//return { result[0], result[1], result[2] };
	return result;
}


void ObjLoader::constructBuffer(std::vector<face> &faces, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<GLfloat> &buffer) // const?
{
	for (int i = 0; i < faces.size(); i++)
	{
		buffer.push_back(vertices[faces[i].x.v - 1].x);
		buffer.push_back(vertices[faces[i].x.v - 1].y);
		buffer.push_back(vertices[faces[i].x.v - 1].z);
		//
		buffer.push_back(normals[faces[i].x.vn - 1].x);
		buffer.push_back(normals[faces[i].x.vn - 1].y);
		buffer.push_back(normals[faces[i].x.vn - 1].z);
		//
		buffer.push_back(vertices[faces[i].y.v - 1].x);
		buffer.push_back(vertices[faces[i].y.v - 1].y);
		buffer.push_back(vertices[faces[i].y.v - 1].z);
		//
		buffer.push_back(normals[faces[i].y.vn - 1].x);
		buffer.push_back(normals[faces[i].y.vn - 1].y);
		buffer.push_back(normals[faces[i].y.vn - 1].z);
		//
		buffer.push_back(vertices[faces[i].z.v - 1].x);
		buffer.push_back(vertices[faces[i].z.v - 1].y);
		buffer.push_back(vertices[faces[i].z.v - 1].z);
		//
		buffer.push_back(normals[faces[i].z.vn - 1].x);
		buffer.push_back(normals[faces[i].z.vn - 1].y);
		buffer.push_back(normals[faces[i].z.vn - 1].z);
	}
}