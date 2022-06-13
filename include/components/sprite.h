#ifndef SPRITE_H
#define SPRITE_H
#include "texture.h"
#include "shader.h"
#include "rect.h"


typedef struct Sprite {
	Texture texture;
	ShaderProgram shader;
	uint16_t tex_width;
	uint16_t tex_height;
	Rect src_rect;
} Sprite;
#endif