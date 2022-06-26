#ifndef COMPONENT_DEFS_H
#define COMPONENT_DEFS_H
#include <stddef.h>

#include "sprite.h"
#include "transform.h"
#include "camera.h"
#include "animation.h"
#include "player.h"

typedef enum ComponentType
{
	COMP_SPRITE,
	COMP_TRANSFORM,
	COMP_CAMERA,
	COMP_ANIMATION,
	COMP_PLAYER,
	COMP_NUM
} ComponentType;

extern const size_t COMPONENT_SIZES[COMP_NUM];

#endif