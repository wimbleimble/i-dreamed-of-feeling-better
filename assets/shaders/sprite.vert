#version 330 core
layout (location = 0) in vec2 vertex;

out vec2 texture_coords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat3 texture_window;

void main()
{
	texture_coords = (vec3(vertex, 1.0) * texture_window).xy;
	gl_Position = projection * view * model * vec4(vertex, 0.0, 1.0);
}
