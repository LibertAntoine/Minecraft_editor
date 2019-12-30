#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 5) in uvec2 cubeId;

out vData{
	flat uvec2 cubeId;
} data_vs;

void main()
{
	data_vs.cubeId = cubeId;
	gl_Position = vec4(position, 1);
};

#shader geometry
#version 440 core

layout(points) in;
layout(triangle_strip, max_vertices = 64) out;


in vData{
	flat uvec2 cubeId;
} data_vs[];

out gData
{
	flat uvec2 cubeId;
	flat int face;
} data_gs;

uniform mat4 uMVPMatrix;

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
				data_gs.cubeId = data_vs[0].cubeId;
				data_gs.face = k;
				EmitVertex();
			}
			EndPrimitive();
		}
	}
}

#shader fragment
#version 330 core

in gData
{
	flat uvec2 cubeId;
	flat int face;
} data_gs;

// NOTE: location 0 corresponds to the first index in glDrawBuffers array, so GL_COLOR_ATTACHMENT0
layout(location = 0) out uvec4 fFragCubeId;

// NOTE: uint is a 32-bit unsigned integer
void main()
{
  fFragCubeId = uvec4(data_gs.cubeId.x, data_gs.cubeId.y, data_gs.face, 1);
};
