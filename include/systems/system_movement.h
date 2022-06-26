#ifndef SYSTEM_MOVEMENT_H
#define SYSTEM_MOVEMENT_H
#include "ecs.h"
#include "event_bus.h"

void system_movement_tick(ECS* ecs, EventBus event_bus, float delta_time);

#endif