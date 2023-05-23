#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include <stdint.h>

typedef struct Animation {
    uint8_t start_frame;
    uint8_t num_frames;

} Animation;

#define ANIMATIONS_PER 8

typedef struct Animations {
    Animation list[ANIMATIONS_PER];    
} Animations;
#endif
