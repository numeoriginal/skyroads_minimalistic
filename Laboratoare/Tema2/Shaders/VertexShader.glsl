#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 1) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

// TODO: output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;
out float frag_time;

void main()
{
	// TODO: send output to fragment shader
	float transformedX = v_position.x + cos(v_position.y*8.0f + Time*22.2)*.1f;
	
	
	vec3 newPosition = vec3(transformedX,v_position.y,v_position.z);
	frag_position = newPosition;
	frag_normal = v_normal;
	frag_texture = v_texture;
	frag_color = v_color;
	frag_time = Time;

	// TODO: compute gl_Position
	
	gl_Position = Projection * View * Model * vec4(newPosition,1);
}
