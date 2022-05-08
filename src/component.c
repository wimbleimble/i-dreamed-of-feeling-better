#include "component.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

bool component_array_init(
	ComponentArray* array,
	size_t component_size,
	SystemType subscriptions)
{
	array->entity_to_index = calloc(MAX_ENTITIES, sizeof(size_t));
	array->index_to_entity = calloc(MAX_ENTITIES, sizeof(Entity));
	array->array = calloc(MAX_ENTITIES, component_size);

	if (array->index_to_entity == NULL
		|| array->entity_to_index == NULL
		|| array->array == NULL)
		return false;

	array->component_size = component_size;
	array->subscriptions = subscriptions;
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
	++array->num_components;

	return new_comp;
}

void* component_array_remove(ComponentArray* array, Entity entity)
{
	printf("Implement component array removinggsgssgsg!!!!!");
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
	for (ComponentType type = 0; type < NUM_COMPONENTS; ++type)
	{
		component_array_init(
			&(component_data->components[type]),
			COMPONENT_SIZES[type],
			SUBSCRIPTIONS[type]
		);
	}
}