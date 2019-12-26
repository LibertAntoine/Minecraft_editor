#shader vertex
#version 330 core

layout(location = 0) in vec2 aVertexPosition;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uTranslation;

out vec2 vVertexPosition_world; // Position du sommet dans l'espace world
out vec3 vVertexPosition; // Position du sommet transformé dans l'espace View

void main()
{
  vec4 vertexPosition = vec4(vec3( aVertexPosition, 0 ), 1);
  vVertexPosition = vec3(uMVMatrix * vertexPosition).xyz;

  vVertexPosition_world = vec3(uTranslation * vertexPosition).xy; // Untransformed positions

  gl_Position = uMVPMatrix * vertexPosition;
};

#shader fragment
#version 330 core

in vec2 vVertexPosition_world; // Position du sommet dans l'espace world
in vec3 vVertexPosition; // Position du sommet transformé dans l'espace View

layout(location = 0) out ivec4 fFragSquarePosition;

void main()
{
  fFragSquarePosition = ivec4(floor(vVertexPosition_world.x), floor( vVertexPosition_world.y), 0, 1);
};
