#version 440 core

out vec4 o_color;

in vec2 v_texcoord;

uniform sampler2D u_texture;
uniform vec4 u_color;

void main()
{	
	o_color = texture(u_texture, v_texcoord) * u_color;
}