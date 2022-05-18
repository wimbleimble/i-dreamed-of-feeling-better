#include "resource_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void resource_init(Resources* resources)
{
	// TODO maybe get rid of this.
}

const char* get_asset_directory()
{
	// TODO Better this shit.
}

void resource_set_shader_capacity(Resources* resources, size_t capacity)
{
	// TODO implement dynamic resizing
	assert(resources->capacity == 0);
	assert(resources->shaders == NULL);

	resources->shaders = calloc(capacity, sizeof(ShaderProgram));
	resources->capacity = capacity;
}

char* load_file(const char* path)
{
	// TODO handle errors
	FILE* file = fopen(path, "r");
	assert(file && "Unable to open file.");
	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* buffer = malloc(length + 1);
	if (buffer)
	{
		fread(buffer, 1, length, file);
		buffer[length] = '\0';
	}
	fclose(file);
	return buffer;
}

ShaderProgram resource_load_shader(
	Resources* resources, const char* vertex_file, const char* fragment_file)
{
	assert((resources->num_shaders < resources->capacity)
		&& "Cannot add another shader.");

	char* vertex_source = load_file(vertex_file);
	char* fragment_source = load_file(fragment_file);

	ShaderProgram shader = shader_compile(vertex_source, fragment_source);
	resources->shaders[resources->num_shaders++] = shader;

	free(vertex_source);
	free(fragment_source);
	return shader;
}