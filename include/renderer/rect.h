#ifndef RECT_H
#define RECT_H
#include <stdint.h>

typedef struct Rect {
	uint16_t x;
	uint16_t y;
	uint16_t z;
	uint16_t w;
} Rect;

#endif