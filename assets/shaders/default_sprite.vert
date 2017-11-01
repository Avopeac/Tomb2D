#version 440 core

layout (location = 0) in vec2 i_position;
layout (location = 1) in mat4 i_transform;
layout (location = 5) in vec4 i_color;
layout (location = 6) in vec4 i_animation;
layout (location = 7) in uint i_layer;


out gl_PerVertex
{
	vec4 gl_Position;
};

out vec2 v_texcoord;

flat out vec4 v_color;

flat out vec4 v_animation;

flat out uint v_layer;

uniform mat4 u_viewproj;

void main()
{
	vec4 transformed = i_transform * vec4(i_position.xy, 0, 1);
	gl_Position = u_viewproj * transformed;

	v_texcoord = 0.5 + 0.5 * i_position.xy;
	v_texcoord.y = 1.0 - v_texcoord.y;
	v_color = i_color;
	v_animation = i_animation;
	v_layer = i_layer;	
}