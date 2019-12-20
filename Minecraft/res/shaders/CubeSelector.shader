#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

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

uniform int uCubeID;

// TODO: Check what is the purpose
layout(location = 0) out uvec3 fFragCubeId;

void main()
{
  // NOTE: base 256 storage
  int rest = 0;

  int r = uCubeID / (256 * 256);
  rest = uCubeID % (256 * 256);

  int g = rest / 256;
  rest %= 256;

  int b = rest;

  //fFragCubeId = uvec4(12, 52, 98, 255);
  //fFragCubeId = ivec3(r, g, b);
  fFragCubeId = uvec3(r, g, b);
  //fFragCubeId = uvec4(r, g, b, 1);
  //fFragCubeId = ivec3(0.5f, 0, 0);

};
