#include "ecs.h"
#include "component.h"
#include <stdlib.h>
#include <assert.h>

bool ecs_init(ECS* ecs)
{
	entity_init(&(ecs->entity_data));
	component_init(&(ecs->component_data));
    return true;
}

bool ecs_destroy_entity(ECS* ecs, Entity entity)
{
	ComponentSignature signature = entity_signature(&(ecs->entity_data), entity);
	component_entity_destroy(&(ecs->component_data), entity, signature);
	entity_destroy(&(ecs->entity_data), entity);
}

Entity ecs_create_entity(ECS* ecs)
{
	return entity_create(&(ecs->entity_data));
}

void* ecs_assign_component(ECS* ecs, Entity entity, ComponentType type, void* component)
{
	// TODO check entity exists.
	// TODO check entity doesn't already have component
	assert(type < COMP_NUM);

	ComponentArray* array = &(ecs->component_data.components[type]);
	entity_or_signature(&(ecs->entity_data), entity, COMP_SIG(type));
	return component_array_append(array, component, entity);
}

void ecs_remove_component(ECS* ecs, Entity entity, ComponentType type)
{
	ComponentSignature entity_sig = ecs->entity_data.entity_signatures[entity];
	component_array_remove(ecs->component_data.components + type, entity, entity_sig);
	ecs->entity_data.entity_signatures[entity] = entity_sig ^ COMP_SIG(type);
}

void* ecs_get_component(ECS* ecs, Entity entity, ComponentType type)
{
	// TODO check entity exists.
	// TODO check entity has component
	assert(type < COMP_NUM);
	ComponentArray* array = &(ecs->component_data.components[type]);

	return component_array_get(array, entity);

}
