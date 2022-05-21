#ifndef SPRITE_H
#define SPRITE_H
#include "texture.h"
#include "shader.h"

typedef struct Sprite {
	Texture texture;
	ShaderProgram shader;
} Sprite;
#endif