#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition_vs; // Position du sommet transform� dans l'espace View
out vec3 vNormal_vs; // Normale du sommet transform� dans l'espace View
out vec2 vTexCoords;

void main()
{
	vec4 vertexPosition = vec4(position, 1);
	vec4 vertexNormal = vec4(normal, 0);


	vPosition_vs = vec3(uMVMatrix * vertexPosition);
	vNormal_vs = normal;
	vTexCoords = texCoord;

	gl_Position = uMVPMatrix * vertexPosition;

};



#shader fragment
#version 330 core

in vec3 vPosition_vs; // Position du sommet transform� dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transform� dans l'espace View
in vec2 vTexCoords;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

uniform sampler2D uTex;

out vec4 fFragTexture;

vec3 blinnPhong()
{
	return 
		vec3(uLightIntensity * (
			uKd * max(dot(uLightDir_vs, vNormal_vs), 0.)
			+ uKs * pow(max(dot(normalize(-vPosition_vs), vNormal_vs), 0.), uShininess)
			));
}

void main() {
	fFragTexture = texture(uTex, vTexCoords);
};
