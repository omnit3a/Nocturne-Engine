#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int NE_is_left_mouse_held(lua_State * lState){
	Uint32 mouse_state = 0;

	mouse_state = SDL_GetMouseState(NULL, NULL);
	mouse_state &= SDL_BUTTON(1);
	lua_pushnumber(lState, mouse_state > 0);
	return 1;
}

int NE_is_right_mouse_held(lua_State * lState){
        Uint32 mouse_state = 0;

        mouse_state = SDL_GetMouseState(NULL, NULL);
	mouse_state &= SDL_BUTTON(3);
	lua_pushnumber(lState, mouse_state > 0);
	return 1;
}

int NE_get_mouse_x_distance(lua_State * lState){
        const int start_x = (int) lua_tonumber(lState, 1);
	int new_x = start_x;
	
        SDL_GetMouseState(&new_x, NULL);
	lua_pushnumber(lState, abs(new_x - start_x));
	return 1;
}

int NE_get_mouse_y_distance(lua_State * lState){
        const int start_y = (int) lua_tonumber(lState, 1);	
	int new_y = start_y;
	
        SDL_GetMouseState(NULL, &new_y);
	lua_pushnumber(lState, abs(new_y - start_y));
	return 1;
}

void api_register_input(lua_State * lState){
	lua_register(lState, "is_key_held", NE_is_key_held);
	lua_register(lState, "is_left_mouse_held", NE_is_left_mouse_held);
	lua_register(lState, "is_right_mouse_held", NE_is_right_mouse_held);
	lua_register(lState, "get_mouse_x_distance", NE_get_mouse_x_distance);
	lua_register(lState, "get_mouse_y_distance", NE_get_mouse_y_distance);
}
