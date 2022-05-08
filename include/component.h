#ifndef COMPONENT_H
#define COMPONENT_H
#include <stddef.h>
#include <stdbool.h>
#include "component_defs.h"
#include "entity.h"

typedef struct ComponentArray
{
	size_t component_size;
	size_t num_components;
	SystemType subscriptions;
	void* array;
	size_t* entity_to_index;
	Entity* index_to_entity;
	ComponentType type;
} ComponentArray;

typedef struct ComponentData
{
	ComponentArray components[NUM_COMPONENTS];
} ComponentData;

bool component_init(ComponentData* component_data);
void* component_new(ComponentType type, void* compoenent);
void* component_array_append(ComponentArray* array, void* component, Entity entity);
void* component_array_get(ComponentArray* array, Entity entity);

#define COMP_SIG(type) ((ComponentSignature)(1UL << type))
#endif