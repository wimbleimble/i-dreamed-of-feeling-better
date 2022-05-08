#ifndef ENTITY_H
#define ENTITY_H
#include <stdint.h>
#include <stdbool.h>

#define MAX_ENTITIES 4096

//-- Types ---------------------------------------------------------------------
typedef uint16_t Entity;
typedef uint32_t ComponentSignature;

typedef struct EntitiyQueueNode {
	Entity value;
	struct EntitiyQueueNode* next;
} EntityQueueNode;

typedef struct EntityQueue {
	EntityQueueNode* front;
	EntityQueueNode* back;
} EntityQueue;

typedef struct EntityData {
	EntityQueue entity_queue;
	ComponentSignature* entity_signatures;
	uint16_t num_entities;
} EntityData;

bool entity_init(EntityData* entity_data);

Entity entity_create(EntityData* entity_data);
void entity_destroy(EntityData* entity_data, Entity entity);
void entity_set_signature(EntityData* entity_data, Entity entity, ComponentSignature signature);
void entity_or_signature(EntityData* entity_data, Entity entity, ComponentSignature signature);
ComponentSignature entity_signature(EntityData* entity_data, Entity entity);

#endif