#version 440 core

layout (location = 0) in vec2 i_position;

out gl_PerVertex
{
	vec4 gl_Position;
};

out vec2 v_texcoord;

uniform mat4 u_mvp;

void main()
{
	gl_Position = u_mvp * vec4(i_position.xy, 0, 1);

	v_texcoord = 0.5 + 0.5 * i_position.xy;
	v_texcoord.y = 1.0 - v_texcoord.y;	
}