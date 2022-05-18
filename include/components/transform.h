#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <stdint.h>
typedef struct Transform {
	uint8_t x;
	uint8_t y;
	uint8_t rot;
	uint8_t scale;
} Transform;

#endif