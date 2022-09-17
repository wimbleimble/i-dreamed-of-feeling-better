#include "system_defs.h"
#include "system_animation.h"
#include "system_movement.h"
#include "system_render.h"

const EventHandler EVENT_HANDLERS[SYS_NUM] = {
    NULL,                   // Render
	system_animation_event, // Animation
	NULL                    // Movement
};
