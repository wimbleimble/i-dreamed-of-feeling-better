#ifndef ANIMATION_H
#define ANIMATION_H
#include <stdint.h>

// TODO think about sizes here
typedef struct Animation {
	// Animation State
	uint8_t fps;
	uint8_t current_frame;
	float t_since_frame;

	// Animation Defintions
	uint8_t sheet_frames;
	uint8_t start_frame;
	uint8_t num_frames;

} Animation;

#endif