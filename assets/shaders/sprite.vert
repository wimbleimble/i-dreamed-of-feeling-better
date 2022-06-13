#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 texture_coords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat3 texture_window;

void main()
{
	texture_coords = (texture_window * vec3(vertex.xy, 1.0)).xy;
	gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
}
