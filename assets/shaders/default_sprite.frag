#version 440 core

out vec4 o_color;

in vec2 v_texcoord;

in vec4 v_color;

uniform sampler2D u_texture;

void main()
{
	o_color = textureLod(u_texture, v_texcoord, 0) * v_color;
}