#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>
#include <GL/glu.h>
#include <stdbool.h>

typedef GLuint Texture;

Texture texture_create(uint32_t width, uint32_t height, bool alpha, uint8_t* data);
void texture_bind(Texture texture);

#endif