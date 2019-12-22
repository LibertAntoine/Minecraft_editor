#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

void main() {
	gl_Position = vec4(position, 1.0);
}

#shader fragment
#version 330 core

in vec2 tex_coord;

uniform sampler2D tex[6];

out vec4 fFragTexture;

void main()
{
		fFragTexture = texture(tex[gl_PrimitiveID], tex_coord);
};


#shader geometry
#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 64) out;

out vec2 tex_coord;

uniform mat4 uMVPMatrix;

const vec2 texc[4] = vec2[](vec2(0, 0), // texture coordinates
	vec2(1, 0),
	vec2(0, 1),
	vec2(1, 1));


void main() {
	vec4 offset[24] = vec4[](
		vec4(0, 1, 0, 0.0), //top face
		vec4(1, 1, 0, 0.0),
		vec4(1, 1, 1, 0.0),
		vec4(0, 1, 1, 0.0),

		vec4(0, 0, 0, 0.0), //bottom face
		vec4(1, 0, 0, 0.0),
		vec4(1, 0, 1, 0.0),
		vec4(0, 0, 1, 0.0),

		vec4(0, 0, 0, 0.0), //left face
		vec4(0, 1, 0, 0.0),
		vec4(0, 1, 1, 0.0),
		vec4(0, 0, 1, 0.0),

		vec4(1, 1, 0, 0.0), //right face
		vec4(1, 1, 1, 0.0),
		vec4(1, 0, 1, 0.0),
		vec4(1, 0, 0, 0.0),

		vec4(1, 0, 1, 0.0), //rear face
		vec4(1, 1, 1, 0.0),
		vec4(0, 1, 1, 0.0),
		vec4(0, 0, 1, 0.0),

		vec4(0, 0, 0, 0.0), //front face
		vec4(0, 1, 0, 0.0),
		vec4(1, 1, 0, 0.0),
		vec4(1, 0, 0, 0.0));

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
}