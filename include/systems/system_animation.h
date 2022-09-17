#ifndef SYSTEM_ANIMATION
#define SYSTEM_ANIMATION
#include "ecs.h"
#include "event_bus.h"

void system_animation_event(ECS* ecs, void* event);
void system_animation_tick(ECS* ecs, float delta_time);

#endif