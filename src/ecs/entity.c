#include "entity.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

//-- Queue Functions -----------------------------------------------------------
bool id_queue_push(EntityData* entity_data, Entity entity)
{
	EntityQueueNode* new_node = (EntityQueueNode*)calloc(1, sizeof(EntityQueueNode));
	if (new_node == NULL)
		return false;

	new_node->value = entity;
	new_node->next = NULL;

	if (entity_data->entity_queue.front == NULL
		&& entity_data->entity_queue.back == NULL)
	{
		entity_data->entity_queue.front = new_node;
		entity_data->entity_queue.back = new_node;
	}
	else
	{
		entity_data->entity_queue.back->next = new_node;
		entity_data->entity_queue.back = new_node;
	}
	return true;
}

Entity id_queue_pop(EntityData* entity_data)
{
	assert(entity_data->entity_queue.front != NULL && "Queue is empty.");
	Entity val = entity_data->entity_queue.front->value;
	EntityQueueNode* new_front = entity_data->entity_queue.front->next != NULL ?
		entity_data->entity_queue.front->next : NULL;
	free(entity_data->entity_queue.front);
	entity_data->entity_queue.front = new_front;
	return val;
}

//-- Public Functions ---------------------------------------------------------
bool entity_init(EntityData* entity_data)
{
	entity_data->entity_signatures = calloc(MAX_ENTITIES, sizeof(ComponentSignature));
	for (int i = 0; i < MAX_ENTITIES; ++i)
		if (!id_queue_push(entity_data, (Entity)i))
			return false;
	return true;
}

Entity entity_create(EntityData* entity_data)
{
	assert(entity_data->num_entities < MAX_ENTITIES && "Too many entities!");
	Entity entity = id_queue_pop(entity_data);
	++(entity_data->num_entities);
	return entity;
}

void entity_destroy(EntityData* entity_data, Entity entity)
{
	// TODO maybe check that entity value is actually in use?
	assert(entity < MAX_ENTITIES && "Entity ID exceeds max entities.");
	assert(entity_data->num_entities > 0 && "No entities in play.");
	entity_data->entity_signatures[entity] = 0;
	id_queue_push(entity_data, entity);
	--(entity_data->num_entities);
}

void entity_set_signature(EntityData* entity_data, Entity entity, ComponentSignature signature)
{
	assert(entity < MAX_ENTITIES && "Entity ID exceeds max entities.");
	entity_data->entity_signatures[entity] = signature;
}

void entity_or_signature(EntityData* entity_data, Entity entity, ComponentSignature signature)
{
	assert(entity < MAX_ENTITIES && "Entity ID exceeds max entities.");
	entity_data->entity_signatures[entity] |= signature;
}

ComponentSignature entity_signature(EntityData* entity_data, Entity entity)
{
	// TODO make aware if accessed entity actually exists.
	assert(entity < MAX_ENTITIES && "Entity ID exceeds max entities.");
	return entity_data->entity_signatures[entity];
}
