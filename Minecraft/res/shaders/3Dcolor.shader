#shader vertex
#version 330 core

// NOTE: IMPORTANT, input numbers and location id must necessarily match with both 3D and 3Dcolor shaders otherwise values mess up
// It is the offset that gets wrong and no longer match the cube's raw properties

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float face;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition_vs; // Position du sommet transform� dans l'espace View
out vec3 vNormal_vs; // Normale du sommet transform� dans l'espace View
out vec2 vTexCoords;
out vec4 vColor;

void main()
{
  vec4 vertexPosition = vec4(position, 1.f);
  vec4 vertexNormal = vec4(normal, 0);

  vPosition_vs = vec3(uMVMatrix * vertexPosition);
  vNormal_vs = vec3(uNormalMatrix * vertexNormal);

  vTexCoords = texCoord;
  if ( face == 1.f ) {
    vColor = vec4(0.5f, 0.f, 0.f, 1.0f);
  }

  else if ( face == 2.f ) {
    vColor = vec4(0.f, 0.5f, 0.f, 1.0f);
  }

  else if ( face == 3.f ) {
    vColor = vec4(0.f, 0.f, 0.5f, 1.0f);
  }

  else if ( face == 4.f ) {
    vColor = vec4(0.f, 0.5f, 0.5f, 1.0f);
  }

  else if ( face == 5.f ) {
    vColor = vec4(0.5f, 0.f, 0.5f, 1.0f);
  }

  else if ( face == 6.f ) {
    vColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
  }

  else {
    vColor = vec4(0.f, 1.f, 1.f, 1.0f);
  }
  gl_Position = uMVPMatrix * vertexPosition;
};



#shader fragment
#version 330 core

in vec3 vPosition_vs; // Position du sommet transform� dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transform� dans l'espace View
in vec2 vTexCoords;
in vec4 vColor;

uniform vec3 uColor;

out vec4 fFragColor;

void main()
{
  fFragColor = vColor;
};
