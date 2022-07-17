#ifndef ECS_H
#define ECS_H
#include <stdbool.h>
#include "entity.h"
#include "component.h"

typedef struct ECS {
	EntityData entity_data;
	ComponentData component_data;
} ECS;

bool ecs_init(ECS* ecs);
bool ecs_destroy_entity(ECS* ecs, Entity entity);
Entity ecs_create_entity(ECS* ecs);
void* ecs_assign_component(ECS* ecs, Entity entity, ComponentType type, void* component);
void ecs_remove_component(ECS* ecs, Entity entity, ComponentType type);
void* ecs_get_component(ECS* ecs, Entity entity, ComponentType type);

#endif