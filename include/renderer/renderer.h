#ifndef RENDERER_H
#define RENDERER_H
#include <stdbool.h>
#include <stdint.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

typedef GLuint VAO;

typedef struct RenderContext {
	SDL_Window* window;
	SDL_GLContext gl_context;
	VAO quadVAO;
} RenderContext;

bool renderer_init(
	RenderContext* render_context,
	const char* title, int win_width, int win_height, uint32_t win_flags);

bool renderer_fullscreent(bool fullscreen);

#endif