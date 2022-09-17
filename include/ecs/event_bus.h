#ifndef EVENT_BUS_H
#define EVENT_BUS_H
#include "system_defs.h"

#define BUS_CAPACITY 512

typedef struct EventBuffer {
	void* head;
	void* tail;
	void* buffer;
} EventBuffer;

typedef struct EventBus {
	size_t event_size;
	// TODO Dynamic?
	EventBuffer buffers[SYS_NUM];
} EventBus;

void event_bus_init(EventBus* bus);
void event_bus_post(EventBus* bus, SystemSignature destination, void* event);
void event_bus_dispatch(EventBus* bus, ECS* ecs);

#endif