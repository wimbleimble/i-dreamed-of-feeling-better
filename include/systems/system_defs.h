#ifndef SYSTEM_DEFS_H
#define SYSTEM_DEFS_H
#include "system.h"

typedef enum SystemType
{
	SYS_RENDER,
	SYS_ANIMATION,
	SYS_MOVEMENT,
	SYS_NUM
} SystemType;

extern const EventHandler EVENT_HANDLERS[SYS_NUM];

#endif