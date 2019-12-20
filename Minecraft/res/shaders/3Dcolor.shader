#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition_vs; // Position du sommet transform� dans l'espace View
out vec3 vNormal_vs; // Normale du sommet transform� dans l'espace View

void main()
{
	vec4 vertexPosition = vec4(position, 1);
	vec4 vertexNormal = vec4(normal, 0);

	vPosition_vs = vec3(uMVMatrix * vertexPosition);
	vNormal_vs = vec3(uNormalMatrix * vertexNormal);

	gl_Position = uMVPMatrix * vertexPosition;
};



#shader fragment
#version 330 core

in vec3 vPosition_vs; // Position du sommet transform� dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transform� dans l'espace View


uniform vec3 uColor;

out vec4 fFragColor;

void main()
{
	fFragColor = vec4(uColor.x, uColor.y, uColor.z, 1.0f);
};