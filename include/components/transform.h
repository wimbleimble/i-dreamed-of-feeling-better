#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <stdint.h>
#include <cglm/cglm.h>

// This is a floating point precision error waiting to happen.
typedef struct Transform {
	vec2 position;
	vec2 size;
} Transform;

#endif