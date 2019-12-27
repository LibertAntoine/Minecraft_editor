#shader vertex
#version 330 core

layout(location = 4) in vec3 position;
layout(location = 3) in vec3 color;

out vData
{
	vec4 color;
} vertex;



out vec3 color_vs;

void main() {
	gl_Position = vec4(position, 1.0);
	vertex.color = vec4(color, 1);
}

#shader fragment
#version 330 core

in vec2 tex_coord;


in fData
{
	vec4 color;
} frag;


uniform sampler2D tex[6];

out vec4 fFragTexture;

void main()
{
	//fFragTexture = vec4(0.5,0.5, 0.5, 1);
	fFragTexture = frag.color;
};


#shader geometry
#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 64) out;

out vec2 tex_coord;


in vData
{
	vec4 color;
}vertex[];

out fData
{
	vec4 color;
}frag;


uniform mat4 uMVPMatrix;

const vec2 texc[4] = vec2[](vec2(0, 0), // texture coordinates
	vec2(1, 0),
	vec2(0, 1),
	vec2(1, 1));

const vec4 cubeVerts[8] = vec4[8](
	vec4(0, 0, 0, 1),  //LB   0
	vec4(0, 1, 0, 1), //L T   1
	vec4(1, 0, 0, 1), //R B    2
	vec4(1, 1, 0, 1),  //R T   3
						//back face
	vec4(0, 0, 1, 1), // LB  4
	vec4(0, 1, 1, 1), // LT  5
	vec4(1, 0, 1, 1),  // RB  6
	vec4(1, 1, 1, 1)  // RT  7
	);

const int  cubeIndices[24] = int[24]
(
	0, 1, 2, 3, //front
	7, 6, 3, 2, //right
	7, 5, 6, 4,  //back or whatever
	4, 0, 6, 2, //btm 
	1, 0, 5, 4, //left
	3, 1, 7, 5
	);

void main() {
	/*
	int i, j, k;
	for (i = 0; i < gl_in.length(); ++i) {          // for each input vertex generate a cube
		for (k = 0; k < offset.length() / 4; ++k) { // for each face of the cube

			gl_PrimitiveID = k; // Must set this, otherwise it will be undefined in the FS

			for (j = 0; j < 4; ++j) {               // for each vertex per face
				gl_Position = uMVPMatrix * (gl_in[i].gl_Position + offset[j + k * 4]);
				tex_coord = texc[j];
				EmitVertex();
			}
			EndPrimitive();
		}
	}
	*/

	for (int j = 0; j < gl_in.length(); j++) {
		for (int k = 0; k < 6; ++k) {
			for (int i = 0; i < 4; i++) {
				int v = cubeIndices[i + k*4];
				gl_Position = uMVPMatrix * (gl_in[j].gl_Position + cubeVerts[v]);
				frag.color = vertex[j].color;
				EmitVertex();
			}
			EndPrimitive();
		}
		
	}
}