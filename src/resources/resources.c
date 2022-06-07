#include "resources.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stb_image.h"

void resources_init(Resources* resources, size_t shader_capacity, size_t texture_capacity)
{
	resources_set_shader_capacity(resources, shader_capacity);
	resources_set_texture_capacity(resources, texture_capacity);
}

//-- Util ----------------------------------------------------------------------
const char* get_asset_directory()
{
	// TODO Better this shit.
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

//-- Shaders -------------------------------------------------------------------

void resources_set_shader_capacity(Resources* resources, size_t shader_capacity)
{
	// TODO implement dynamic resizing
	assert(resources->shader_capacity == 0);
	assert(resources->shaders == NULL);

	resources->shaders = calloc(shader_capacity, sizeof(ShaderProgram));
	resources->shader_capacity = shader_capacity;
}

ShaderProgram resources_load_shader(
	Resources* resources, const char* vertex_file, const char* fragment_file)
{
	assert((resources->num_shaders < resources->shader_capacity)
		&& "Cannot add another shader.");

	char* vertex_source = load_file(vertex_file);
	char* fragment_source = load_file(fragment_file);

	ShaderProgram shader = shader_compile(vertex_source, fragment_source);
	resources->shaders[resources->num_shaders++] = shader;

	free(vertex_source);
	free(fragment_source);
	return shader;
}

//-- Textures ------------------------------------------------------------------

void resources_set_texture_capacity(Resources* resources, size_t texture_capacity)
{
	assert(resources->texture_capacity == 0);
	assert(resources->textures == NULL);

	resources->textures = calloc(texture_capacity, sizeof(Texture));
	resources->texture_capacity = texture_capacity;
}

Texture resources_load_texture(Resources* resources, const char* file, bool alpha)
{
	assert((resources->num_textures < resources->texture_capacity)
		&& "Cannot add another texture. Increase texture capacity");
	stbi_set_flip_vertically_on_load(true);
	int width, height, channels;
	uint8_t* data = stbi_load(file, &width, &height, &channels, 0);
	assert(data && "Failed to load image");

	Texture texture = texture_create(width, height, alpha, data);
	stbi_image_free(data);

	resources->textures[resources->num_textures++] = texture;
	return texture;
}