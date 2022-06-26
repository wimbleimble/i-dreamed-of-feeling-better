#include "event_bus.h"
#include <stdlib.h>

void event_bus_init(EventBus bus)
{
	for(size_t type = 0; type < SYS_NUM; ++type)
		bus[type].head = bus[type].tail = bus[type].buffer =
			calloc(BUS_CAPACITY, sizeof(Event));
}

void event_buffer_push(EventBuffer* buffer, Event event)
{
	// TODO bounds checking and loop around
	*buffer->head++ = event;
}
void event_buffer_dispatch(EventBuffer* buffer, EventHandler handler, ECS* ecs)
{
	// TODO bounds checking and loop around
	for (; buffer->tail != buffer->head; ++buffer->tail)
		handler(ecs, *buffer->tail);
}

void event_bus_post(EventBus bus, SystemSignature destination, Event event)
{
	for (SystemType type = 0; type < SYS_NUM; ++type)
		if (SYS_SIG(type) & destination)
			event_buffer_push(&bus[type], event);
}

void event_bus_dispatch(EventBus bus, ECS* ecs)
{
	for (SystemType type = 0; type < SYS_NUM; ++type)
		event_buffer_dispatch(&bus[type], EVENT_HANDLERS[type], ecs);
}