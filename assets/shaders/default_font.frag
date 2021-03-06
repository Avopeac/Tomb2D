#version 440 core

out vec4 o_color;

in vec2 v_texcoord;

uniform sampler2D u_texture;

uniform vec4 u_color;

void main()
{	
	o_color = vec4(textureLod(u_texture, v_texcoord, 0).r) * u_color;
}