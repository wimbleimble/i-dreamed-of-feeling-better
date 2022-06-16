#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>
#include <GL/glu.h>
#include <stdbool.h>

typedef GLuint TextureID;

typedef struct Texture {
	TextureID id;
	uint16_t width;
	uint16_t height;
} Texture;

Texture texture_create(uint32_t width, uint32_t height, bool alpha, uint8_t* data);
void texture_bind(TextureID texture);

#endif