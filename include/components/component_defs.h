#ifndef COMPONENT_DEFS_H
#define COMPONENT_DEFS_H
#include <stddef.h>

#include "sprite.h"
#include "transform.h"
#include "camera.h"

typedef enum ComponentType
{
	SPRITE,
	TRANSFORM,
	CAMERA,
	NUM_COMPONENTS
} ComponentType;

extern const size_t COMPONENT_SIZES[NUM_COMPONENTS];

#endif