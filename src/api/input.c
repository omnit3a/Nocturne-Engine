#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <lua_headers.h>
#include <engine/sdl.h>
#include <api/input.h>

int NE_is_key_held(lua_State * lState){
	SDL_Event event;
        const char * key_name;
	SDL_Keycode keycode;
	SDL_Scancode scancode;
	const Uint8 * key_states;
	
        key_name = lua_tostring(lState, 1);
	keycode = SDL_GetKeyFromName(key_name);
	scancode = SDL_GetScancodeFromKey(keycode);

	SDL_PollEvent(&event);	
	key_states = SDL_GetKeyboardState(NULL);
	if (key_states[scancode]){
		lua_pushboolean(lState, 1);
		SDL_Delay(100);
		return 1;
	}

	lua_pushboolean(lState, 0);
	return 1;
}

void api_register_input(lua_State * lState){
	lua_register(lState, "is_key_held", NE_is_key_held);
}
