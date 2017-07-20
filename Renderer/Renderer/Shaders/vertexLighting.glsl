#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Norm;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float time;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(Pos, 1.0);
	FragPos = vec3(modelMatrix * vec4(Pos, 1.0));
	Normal = mat3(transpose(inverse(modelMatrix))) * Norm;
}