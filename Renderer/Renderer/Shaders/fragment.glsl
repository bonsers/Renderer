#version 330

in vec4 vertexColor;

out vec4 fragColor;

uniform float time;

void main()
{
    fragColor = vec4(0.7, sin(time) * 1.0, 0.0, 1.0);
}