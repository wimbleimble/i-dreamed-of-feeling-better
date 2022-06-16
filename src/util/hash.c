#include "hash.h"

uint64_t djb2(const char* str)
{
	uint32_t hash = 5381;
	uint8_t c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c;

	return hash;
}