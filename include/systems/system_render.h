#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include "ecs.h"
#include "renderer.h"

void system_render_update(ECS* ecs, RenderContext* render_context);
// TODO Event handling
void system_render_handle_events(ECS* ecs, void* event_thing);

#endif