#ifndef SYSTEM_H
#define SYSTEM_H
#include <stdint.h>

typedef uint8_t SystemSignature;

typedef enum SystemType {
	RENDER,
	NUM_SYSTEMS
} SystemType;

#define SYS_SIG(type) ((SystemSignature)(1UL << type))

#endif