#version 440 core

out vec4 o_color;

in vec2 v_texcoord;

flat in vec4 v_color;

flat in vec4 v_animation;

flat in uint v_layer;

uniform sampler2D u_texture;

void main()
{	
	/*vec2 current_frame;
	current_frame.x = int(v_animation.z) % int(v_animation.x);
	current_frame.y = int(v_animation.z) / int(v_animation.x);*/


	vec2 frame_texcoord = v_texcoord;
	frame_texcoord.x = frame_texcoord.x / v_animation.x; // + current_frame.x / v_animation.z;
	frame_texcoord.y = frame_texcoord.y / v_animation.y; // + current_frame.y / v_animation.w;

	o_color = textureLod(u_texture, frame_texcoord, 0) * v_color;
}