#ifndef RENDERER_H
#define RENDERER_H
#include <stdbool.h>
#include <stdint.h>

bool renderer_init(
	const char* title, int win_width, int win_height, uint32_t win_flags);

bool renderer_fullscreent(bool fullscreen);

bool renderer_clean();

#endif