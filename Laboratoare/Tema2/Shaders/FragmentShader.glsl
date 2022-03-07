#version 330

// TODO: get values from fragment shader
in vec3 frag_normal;
in vec3 frag_position;
in vec2 frag_texture;
in vec3 frag_color;
in float frag_time;

layout(location = 0) out vec4 out_color;


void main()
{
	// TODO: write pixel out color
	out_color = vec4(frag_color.x ,frag_color.y * cos(frag_time) ,frag_color.z, 1);
	
}