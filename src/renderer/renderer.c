#include <assert.h>
#include <stdio.h>

#include "renderer.h"

VAO generate_quad_vao()
{
	const float vertices[] = {
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	GLuint vbo;
	VAO vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return vao;
}

bool renderer_init(
	RenderContext* render_context,
	const char* title, int win_width, int win_height, uint32_t win_flags)
{

	// Initialise SDL
	SDL_Init(SDL_INIT_VIDEO);
	render_context->window = SDL_CreateWindow(
		title, 0, 0, win_width, win_height, win_flags);
	assert(render_context->window && "Window == NULL");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	render_context->gl_context = SDL_GL_CreateContext(render_context->window);
	assert(render_context->gl_context && "GL_CONTEXT == NULL");

	// TODO optional vsync
	// Uncomment me to make fps go pchooooo
	//SDL_GL_SetSwapInterval(0);

	// Initialise GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		const GLubyte* string = gluErrorString(err);
		printf("GLError: %s", string);
		return false;
	}
	if (!GLEW_VERSION_3_3)
		return false;

	render_context->quad_vao = generate_quad_vao();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// TODO dynamic viewport
	glViewport(0, 0, win_width, win_height);
	return true;
}

void renderer_draw_2D_sprite(
	const RenderContext* render_context,
	const Sprite* sprite,
	const Rect* frame,
	const vec2 position,
	const vec2 size,
	const vec2 camera_position,
	const vec2 camera_size)
{
	mat4 model;
	vec3 translate = { position[0], position[1], 0.0f };
	glm_translate_make(model, translate);

	vec3 scale = { size[0], size[1], 1.0f };
	glm_scale(model, scale);

	mat4 view;
	vec3 eye = { camera_position[0], camera_position[1], 0.5f };
	vec3 direction = { 0.0f, 0.0f, -1.0f };
	vec3 up = { 0.0f, 1.0f, 0.0f };
	glm_look(eye, direction, up, view);

	mat4 projection;
	glm_ortho(
		-camera_size[0] / 2.0f,
		camera_size[0] / 2.0f,
		-camera_size[1] / 2.0f,
		camera_size[1] / 2.0f,
		-1.0f, 1.0f, projection);

	// magic numbers!
	const float sx =
		(float)(frame->z - frame->x) / sprite->texture.width;
	const float sy =
		-(float)(frame->y - frame->w) / sprite->texture.height;
	const float tx =
		(float)frame->x / sprite->texture.width;
	const float ty =
		-(float)frame->w / sprite->texture.height + 1;

	mat3 texture_matrix = {
		sx,   0.0f, tx,
		0.0f, sy,   ty,
		0.0f, 0.0f, 1.0f
	};

	shader_use(sprite->shader);
	shader_set_matrix_4(sprite->shader, "model", model);
	shader_set_matrix_4(sprite->shader, "view", view);
	shader_set_matrix_4(sprite->shader, "projection", projection);
	shader_set_matrix_3(sprite->shader, "texture_window", texture_matrix);
	glActiveTexture(GL_TEXTURE0);
	texture_bind(sprite->texture.id);

	glBindVertexArray(render_context->quad_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


void renderer_set_clear_colour(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void renderer_clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void renderer_swap_buffer(RenderContext* render_context)
{
	SDL_GL_SwapWindow(render_context->window);
}

bool renderer_fullscreen(bool fullscreen)
{
}