#shader vertex
#version 440 core

uniform vec3 uPosition;

void main() {
	gl_Position = vec4(position, 1);
}

#shader fragment
#version 440 core

in vec2 tex_coord;

out vec4 fFragTexture;

uniform sampler2D uTex;

void main()
{
	fFragTexture = vec4(texture(uTex, vec3(vTexCoords.xy, 0)));
};


#shader geometry
#version 440 core

layout(points) in;
layout(triangle_strip, max_vertices = 64) out;

out vec2 tex_coord;

uniform mat4 uMVPMatrix;

const vec2 texc[4] = vec2[](vec2(0, 0), // texture coordinates
	vec2(1, 0),
	vec2(0, 1),
	vec2(1, 1));

const vec4 cubeVerts[8] = vec4[8](
	vec4(0, 0, 0, 1),  //LB  0
	vec4(0, 1, 0, 1),  //LT  1
	vec4(1, 0, 0, 1),  //RB  2
	vec4(1, 1, 0, 1),  //RT  3
					   //back face
	vec4(0, 0, 1, 1),  //LB  4
	vec4(0, 1, 1, 1),  //LT  5
	vec4(1, 0, 1, 1),  //RB  6
	vec4(1, 1, 1, 1)   //RT  7
	);

const int  cubeIndices[24] = int[24]
(
	0, 1, 2, 3, //front
	7, 6, 3, 2, //right
	7, 5, 6, 4, //back or whatever
	4, 0, 6, 2, //btm 
	1, 0, 5, 4, //left
	3, 1, 7, 5
	);

void main() {
	for (int j = 0; j < gl_in.length(); j++) {
		for (int k = 0; k < 6; ++k) {
			for (int i = 0; i < 4; i++) {
				int v = cubeIndices[i + k * 4];
				gl_Position = uMVPMatrix * (gl_in[j].gl_Position + cubeVerts[v]);
				data_gs.tex_coord = texc[i];
				EmitVertex();
			}
			EndPrimitive();
		}	
	}
}