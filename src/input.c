#include "input.h"
#include <SDL2/SDL.h>

bool input_key_state(size_t key)
{
	// Eh. Ugly.
	static bool initialized = false;
	static uint8_t* key_state;
	if (!initialized)
	{
		key_state = (uint8_t*)SDL_GetKeyboardState(NULL);
		initialized = true;
	}

	return key_state[key];
}

