#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include "ecs.h"

void system_render_update(ECS* ecs);
// TODO Event handling
void system_render_handle_events(ECS* ecs, void* event_thing);

#endif