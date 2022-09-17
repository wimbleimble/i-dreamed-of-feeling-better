#ifndef SYSTEM_H
#define SYSTEM_H
#include <stdint.h>
#include "system_defs.h"
#include "ecs.h"

typedef uint32_t SystemSignature;
#define SYS_SIG(type) ((SystemSignature)(1UL << type))

typedef void (*EventHandler)(ECS*, void*);
#endif