#ifndef PLAYER_H
#define PLAYER_H
#include <stdint.h>
#include "cglm/cglm.h"

typedef enum PlayerState {
	IDLE  = 0,
	UP    = 1,
	DOWN  = 2,
	LEFT  = 4,
	RIGHT = 8
} PlayerState;

typedef struct Player {
	// Pixels / 0.1s
	// not using Pixels per second because that's why.
	uint8_t speed;
	float run_mult; 
	PlayerState state;
} Player;

#endif