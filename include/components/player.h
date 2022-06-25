#ifndef PLAYER_H
#define PLAYER_H
#include <stdint.h>

typedef struct Player {
	// Pixels / 0.1s
	// not using Pixels per second because that's why.
	uint8_t speed;
	float run_mult; 
} Player;

#endif