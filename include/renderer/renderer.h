#ifndef RENDERER_H
#define RENDERER_H
#include <stdbool.h>
#include <stdint.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include <cglm/cglm.h>

#include "sprite.h"
#include "rect.h"

typedef GLuint VAO;

typedef struct RenderContext {
	SDL_Window* window;
	SDL_GLContext gl_context;
	VAO quad_vao;
} RenderContext;

bool renderer_init(
	RenderContext* render_context,
	const char* title, int win_width, int win_height, uint32_t win_flags);

void renderer_draw_2D_sprite(
	const RenderContext* render_context,
	const Sprite* sprite,
	const Rect* frame,
	const vec2 position,
	const vec2 size,
	const vec2 camera_position,
	const vec2 camera_size);

void renderer_set_clear_colour(float r, float g, float b, float a);
void renderer_clear();
void renderer_swap_buffer(RenderContext* render_context);

bool renderer_fullscreent(bool fullscreen);

#endif