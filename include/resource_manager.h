#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include "shader.h"
#include <stddef.h>

typedef struct Resources {
	ShaderProgram* shaders;
	size_t num_shaders;
	size_t capacity;

} Resources;

void resource_init(Resources* resources);
void resource_set_shader_capacity(Resources* resources, size_t capacity);
ShaderProgram resource_load_shader(
	Resources* resources, const char* vertex_file, const char* fragment_file);

#endif