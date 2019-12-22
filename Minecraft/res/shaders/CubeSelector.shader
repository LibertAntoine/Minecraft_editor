#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 texCoord;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;

out vec3 vPosition_vs; // Position du sommet transform� dans l'espace View

void main()
{
	vec4 vertexPosition = vec4(position, 1);

	vPosition_vs = vec3(uMVMatrix * vertexPosition);

	gl_Position = uMVPMatrix * vertexPosition;

};



#shader fragment
#version 330 core

in vec3 vPosition_vs; // Position du sommet transform� dans l'espace View

uniform uint uCubeID[2];

// NOTE: location 0 corresponds to the first index in glDrawBuffers array, so GL_COLOR_ATTACHMENT0
layout(location = 0) out uvec4 fFragCubeId;

// NOTE: uint is a 32-bit unsigned integer
void main()
{
  fFragCubeId = uvec4(uCubeID[0], uCubeID[1], 0, 1);
};
