#include "renderer.h"
#include <assert.h>

VAO generate_quad_vao()
{
	GLuint vbo;
	VAO vao;
	float vertices[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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

	// Initialise GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK)
		return false;
	if (GLEW_VERSION_3_3)
		return false;
	return true;

	render_context->quadVAO = generate_quad_vao();
}

bool renderer_fullscreen(bool fullscreen)
{
}