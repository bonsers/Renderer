#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;

out vec4 vertexColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float time;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(Pos, 1.0);
	vertexColor = vec4(Color, 1.0);
}