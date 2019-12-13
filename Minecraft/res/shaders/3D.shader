#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;


void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
};