#ifndef EVENT_BUS_H
#define EVENT_BUS_H
#include "system_defs.h"

#define BUS_CAPACITY 512

// I don't like this
// events can't hold data. they can only inform that something happens, the
// event handlers have to get the data themselves.
typedef uint64_t Event;

typedef struct EventBuffer {
	Event* head;
	Event* tail;
	Event* buffer;
} EventBuffer;

typedef EventBuffer EventBus[SYS_NUM];

void event_bus_init(EventBus bus);
void event_bus_post(EventBus bus, SystemSignature destination, Event event);
void event_bus_dispatch(EventBus bus, ECS* ecs);

#endif