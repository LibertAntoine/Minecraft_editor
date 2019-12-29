#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 tex1;
layout(location = 3) in vec3 tex2; 
layout(location = 4) in int type;

out vData{
	vec3 position;
	vec4 color;
	vec3 tex1;
	vec3 tex2;
	flat int type;
} data_vs;


void main() {
	gl_Position = vec4(position, 1);
	data_vs.color = vec4(color, 1);
	data_vs.tex1 = tex1;
	data_vs.tex2 = tex2;
	data_vs.type = type;
	data_vs.position = position;
}


#shader geometry
#version 440 core

layout(points) in;
layout(triangle_strip, max_vertices = 100) out;


in vData
{
	vec3 position;
	vec4 color;
	vec3 tex1;
	vec3 tex2;
	flat int type;
} data_vs[];

in vec3 position_vs[];

out gData
{
	vec4 color;
	vec2 tex_coord;
	vec3 normal;
	flat float textureLayer;
	flat int type;
} data_gs;

out vec3 position_gs;

uniform mat4 uMVPMatrix;

const vec2 texc[4] = vec2[](vec2(0, 0), // texture coordinates
	vec2(1, 0),
	vec2(0, 1),
	vec2(1, 1));

const vec3 normc[6] = vec3[](vec3(0, 0, 1), // normal
	vec3(-1, 0, 0),
	vec3(0, 0, -1),
	vec3(0, -1, 0),
	vec3(1, 0, 0),
	vec3(0, 1, 0));

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
	3, 1, 7, 5  //Top
	);

void main() {
	float tex[6] = { data_vs[0].tex1.x, data_vs[0].tex1.y, data_vs[0].tex1.z,
	data_vs[0].tex2.x, data_vs[0].tex2.y, data_vs[0].tex2.z };
	for (int j = 0; j < gl_in.length(); j++) {
		for (int k = 0; k < 6; ++k) {
			for (int i = 0; i < 4; i++) {
				int v = cubeIndices[i + k * 4];
				gl_Position = uMVPMatrix * (gl_in[j].gl_Position + cubeVerts[v]);
				position_gs = data_vs[0].position;
				data_gs.color = data_vs[0].color;
				data_gs.tex_coord = texc[i];
				if (data_vs[0].type == 2) data_gs.textureLayer = tex[k];
				else data_gs.textureLayer = tex[0];
				data_gs.normal = normc[k];
				EmitVertex();
			}
			EndPrimitive();
		}
		data_gs.type = data_vs[0].type;
	}
}


#shader fragment
#version 440 core

in gData
{
	vec4 color;
	vec2 tex_coord;
	vec3 normal;
	flat float textureLayer;
	flat int type;
} data_gs;

in vec3 position_gs;

out vec4 fFragTexture;

uniform sampler2DArray uTexArray;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong()
{
	return
		vec3(uLightIntensity * (
			uKd * max(dot(uLightDir_vs, data_gs.normal), 0.)
			+ uKs * pow(max(dot(normalize(- position_gs), data_gs.normal), 0.), uShininess)
			));
}

void main()
{
	if (data_gs.type == 0)
		fFragTexture = data_gs.color;
	else if (data_gs.type == 1 || data_gs.type == 2)
		fFragTexture = texture(uTexArray, vec3(data_gs.tex_coord.xy, data_gs.textureLayer)) * vec4(blinnPhong(), 1);
};