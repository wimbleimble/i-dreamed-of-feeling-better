#ifndef RESOURCES_H
#define RESOURCES_H
#include "shader.h"
#include "texture.h"
#include <stddef.h>

// TODO redblack tree thing to keep track of what textures have been loaded
// based on filepath. then when you try to load the same one twice it just
// gives you back the old one.
typedef struct Resources {
	ShaderProgram* shaders;
	size_t num_shaders;
	size_t shader_capacity;

	Texture* textures;
	size_t num_textures;
	size_t texture_capacity;

} Resources;

void resources_init(
	Resources* resources, size_t shader_capacity, size_t texture_capacity);

void resources_set_shader_capacity(Resources* resources, size_t shader_capacity);
ShaderProgram resources_load_shader(
	Resources* resources, const char* vertex_file, const char* fragment_file);

void resources_set_texture_capacity(Resources* resources, size_t texture_capacity);
Texture resources_load_texture(Resources* resources, const char* file, bool alpha);

#endif
