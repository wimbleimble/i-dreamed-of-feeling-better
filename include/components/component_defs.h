#ifndef COMPONENT_DEFS_H
#define COMPONENT_DEFS_H
#include <stddef.h>
#include "system.h"

#include "sprite.h"
#include "transform.h"

typedef enum ComponentType
{
	SPRITE,
	TRANSFORM,
	NUM_COMPONENTS
} ComponentType;

extern const size_t COMPONENT_SIZES[NUM_COMPONENTS];

extern const SystemType SUBSCRIPTIONS[NUM_COMPONENTS];

#endif