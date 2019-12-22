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
	vNormal_vs = vec3(uNormalMatrix * vertexNormal);
	vTexCoords = texCoord;

	gl_Position = uMVPMatrix * vertexPosition;

};


#shader fragment
#version 330 core

in vec3 vPosition_vs; // Position du sommet transform� dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transform� dans l'espace View
in vec2 vTexCoords;


uniform sampler2D uTexture1;
uniform sampler2D uTexture2;
uniform sampler2D uTexture3;
uniform sampler2D uTexture4;
uniform sampler2D uTexture5;
uniform sampler2D uTexture6;

out vec4 fFragTexture;

void main()
{
	if (vNormal_vs.x >= 0.9f) {
		
		fFragTexture = texture(uTexture3, vTexCoords);
	}
	else if (vNormal_vs.y >= 0.9f) {
		
		fFragTexture = texture(uTexture5, vTexCoords);
	}
	else if (vNormal_vs.z >= 0.9f) {
		fFragTexture = texture(uTexture1, vTexCoords);
		
	}
	else if (vNormal_vs.x <= -0.9f) {
		fFragTexture = texture(uTexture4, vTexCoords);
	}
	else if (vNormal_vs.y <= -0.9f) {
		 fFragTexture = texture(uTexture6, vTexCoords);
		
	} else if (vNormal_vs.z <= -0.9f) {
		fFragTexture = texture(uTexture2, vTexCoords);
		
	}
};
