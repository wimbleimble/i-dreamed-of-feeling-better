#include "texture.h"

Texture texture_create(uint32_t width, uint32_t height, bool alpha, uint8_t* data)
{

	Texture texture = {
		.width = width,
		.height = height
	};
	glGenTextures(1, &texture.id);
	const GLuint format = alpha ? GL_RGBA : GL_RGB;
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(
		GL_TEXTURE_2D,
		0, format, width, height, 0, format,
		GL_UNSIGNED_BYTE, data);

	// TODO add more parameters for texture filtering, mipmaps, etc.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

void texture_bind(TextureID texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
}