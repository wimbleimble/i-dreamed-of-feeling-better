#include "event_bus.h"

#include <stdlib.h>
#include <string.h>

void event_bus_init(EventBus* bus)
{
    for (size_t type = 0; type < SYS_NUM; ++type)
        bus->buffers[type].head = bus->buffers[type].tail =
            bus->buffers[type].buffer = calloc(BUS_CAPACITY, bus->event_size);
}

static inline void
event_buffer_push(EventBuffer* buffer, void* event, size_t event_size)
{
    // TODO bounds checking and loop around
    memcpy(buffer->head, event, event_size);
    buffer->head = (uint8_t*)buffer->head + event_size;
}
void event_buffer_dispatch(
    EventBuffer* buffer, EventHandler handler, ECS* ecs, size_t event_size)
{
    // TODO bounds checking and loop around
    for (; buffer->tail != buffer->head;
         buffer->tail = (uint8_t*)buffer->tail + event_size)
        handler(ecs, buffer->tail);
}

void event_bus_post(EventBus* bus, SystemSignature destination, void* event)
{
    for (SystemType type = 0; type < SYS_NUM; ++type)
        if (SYS_SIG(type) & destination)
            event_buffer_push(&bus->buffers[type], event, bus->event_size);
}

void event_bus_dispatch(EventBus* bus, ECS* ecs)
{
    for (SystemType type = 0; type < SYS_NUM; ++type)
        event_buffer_dispatch(
            &bus->buffers[type], EVENT_HANDLERS[type], ecs, bus->event_size);
}
