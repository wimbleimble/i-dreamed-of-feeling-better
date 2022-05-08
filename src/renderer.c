#include "renderer.h"
#include <stdio.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

static SDL_Window* window = NULL;
static SDL_GLContext context = NULL;

bool renderer_init(
	const char* title, int win_width, int win_height, uint32_t win_flags)
{
	// Initialise SDL
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(
		title, NULL, NULL, win_width, win_height, win_flags);
	assert(window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	context = SDL_GL_CreateContext(window);

	// Initialise GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK)
		return false;
	if (GLEW_VERSION_3_3)
		return false;
	return true;
}

bool renderer_fullscreen(bool fullscreen)
{
	static bool fullscreen = false;
}

bool renderer_clean()
{

}