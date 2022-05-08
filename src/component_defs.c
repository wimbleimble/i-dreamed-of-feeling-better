#include "component_defs.h"

const size_t COMPONENT_SIZES[NUM_COMPONENTS] = {
	sizeof(Sprite),
	sizeof(Transform)
};

const SystemType SUBSCRIPTIONS[NUM_COMPONENTS] = {
	SYS_SIG(RENDER),
	SYS_SIG(RENDER)
};