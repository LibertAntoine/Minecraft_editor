#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;

out vec3 vPosition_vs; // Position du sommet transformé dans l'espace View

void main()
{
	vec4 vertexPosition = vec4(position, 1);

	vPosition_vs = vec3(uMVMatrix * vertexPosition);

	gl_Position = uMVPMatrix * vertexPosition;

};



#shader fragment
#version 330 core

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View

uniform vec4 u_Color;

out vec4 fFragColor;

void main()
{
	fFragColor = u_Color;
};