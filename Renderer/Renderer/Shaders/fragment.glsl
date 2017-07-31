#version 330

in vec3 Normal;
in vec3 FragPos;

out vec4 fragColor;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	float ambientStrength = 0.4;
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(vec3(1.2, 1.0, 2.0) - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 ambient = ambientStrength * lightColor;    
	fragColor = vec4((ambient + diffuse) * objectColor, 1.0);
}