#version 330 core
in vec2 texture_coords;
out vec4 color;

uniform sampler2D sprite;

void main()
{
	color = texture(sprite, texture_coords);
}
