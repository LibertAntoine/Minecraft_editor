#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 tex1;
layout(location = 3) in vec3 tex2; 
layout(location = 4) in int type;

out vData {
	vec3 color;
	vec3 tex1;
	vec3 tex2;
	flat int type;
} data_vs;

void main() {
	gl_Position = vec4(position, 1);
	data_vs.color = color;
	data_vs.tex1 = tex1;
	data_vs.tex2 = tex2;
	data_vs.type = type;
}



#shader geometry
#version 440 core

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;


in vData
{
	vec3 color;
	vec3 tex1;
	vec3 tex2;
	flat int type;
} data_vs[];

out gData
{
	vec2 tex_coord;
	vec3 color;
	flat float textureLayer;
	flat int type;
} data_gs;

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
	float tex[6] = { data_vs[0].tex1.x, data_vs[0].tex1.y, data_vs[0].tex1.z,
	data_vs[0].tex2.x, data_vs[0].tex2.y, data_vs[0].tex2.z };

	for (int j = 0; j < gl_in.length(); j++) {
		for (int k = 0; k < 6; ++k) {
			for (int i = 0; i < 4; i++) {
				int v = cubeIndices[i + k * 4];
				gl_Position = uMVPMatrix * (gl_in[j].gl_Position + cubeVerts[v]);
				data_gs.color = data_vs[0].color;
				data_gs.tex_coord = texc[i];
				if (data_vs[0].type == 2) data_gs.textureLayer = tex[k];
				else data_gs.textureLayer = tex[0];
				data_gs.type = data_vs[0].type;
				EmitVertex();
			}
			EndPrimitive();
		}
	}
}




#shader fragment
#version 440 core

in gData
{
	vec2 tex_coord;
	vec3 color;
	flat float textureLayer;
	flat int type;
} data_gs;

out vec4 fFragTexture;

uniform sampler2DArray uTexArray;

void main()
{
	if (data_gs.type == 0)
		fFragTexture = vec4(data_gs.color, 1);
	else if (data_gs.type == 1 || data_gs.type == 2)
		fFragTexture = vec4(texture(uTexArray, vec3(data_gs.tex_coord.xy, data_gs.textureLayer)));
};


