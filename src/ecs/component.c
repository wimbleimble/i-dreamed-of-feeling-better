#include "component.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

bool component_array_init(
	ComponentArray* array,
	ComponentType type)
{
	size_t component_size = COMPONENT_SIZES[type];
	array->entity_to_index = calloc(MAX_ENTITIES, sizeof(size_t));
	array->index_to_entity = calloc(MAX_ENTITIES, sizeof(Entity));
	array->array = calloc(MAX_ENTITIES, component_size);

	if (array->index_to_entity == NULL
		|| array->entity_to_index == NULL
		|| array->array == NULL)
		return false;

	array->component_size = component_size;
	array->type = type;
	return true;
}

void component_array_destroy(ComponentArray* array)
{
	assert(array->entity_to_index != NULL
		&& array->index_to_entity != NULL
		&& array->array != NULL
		&& "ComponentArray not initialised.");

	free(array->entity_to_index);
	free(array->index_to_entity);
	free(array->array);
}

void* component_array_append(ComponentArray* array, void* component, Entity entity)
{
	assert(array->num_components < MAX_ENTITIES && "Component array full.");
	assert(component != NULL && "Component is nullptr");
	assert(array != NULL && "Array is nullptr");
	assert(entity < MAX_ENTITIES && "Invalid entity.");

	size_t new_comp_index = array->num_components;
	void* new_comp = array->array + (new_comp_index * array->component_size);

	memcpy(new_comp, component, array->component_size);
	array->entity_to_index[(size_t)entity] = new_comp_index;
	array->index_to_entity[new_comp_index] = entity;
	++(array->num_components);

	return new_comp;
}

void component_array_remove(
	ComponentArray* array, Entity entity, ComponentSignature signature)
{
	assert((COMP_SIG(array->type) & signature)
		&& "Entity doesn't have component.");

	const size_t index = array->entity_to_index[entity];
	uint8_t* comp_ptr = (uint8_t*)array->array + index;

	memset(comp_ptr, 0, array->component_size);

	const size_t num_past = --array->num_components - index;

	// warning - leaves garbage behind at the end of the array. shouldn't
	// matter, but could mean weirdness if something goes wrong elsewhere.
	if(num_past)
		memmove(comp_ptr, comp_ptr + 1, num_past * array->component_size);
}

void component_entity_destroy(
	ComponentData* component_data, Entity entity, ComponentSignature signature)
{
	ComponentSignature trash = signature;
	for (ComponentType type = 0; type < COMP_NUM; ++type)
	{
		// hehe bitwise shit
		trash = trash >> type;
		if (trash & (ComponentSignature)1)
			component_array_remove(
				&(component_data->components[type]), entity, signature);
	}
}

void* component_array_get(ComponentArray* array, Entity entity)
{
	assert(array != NULL && "Array is nullptr");
	assert(entity < MAX_ENTITIES && "Invalid entity.");
	size_t index = array->entity_to_index[entity];
	assert(index < array->num_components && "Index invalid.");
	return array->array + (index * array->component_size);
}

bool component_init(ComponentData* component_data)
{
	for (ComponentType type = 0; type < COMP_NUM; ++type)
	{
		component_array_init(&(component_data->components[type]), type);
	}
}