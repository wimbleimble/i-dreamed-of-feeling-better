#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <stdint.h>
#include "animations.h"

// TODO think about sizes here
typedef struct Animator {
	// Animation State
	uint8_t fps;
	uint8_t current_frame;
	float t_since_frame;

	// Animation Defintions
	uint8_t sheet_frames;
    Animation current_animation;

} Animator;

#endif
