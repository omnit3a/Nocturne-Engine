#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <lua_headers.h>
#include <time.h>
#include <unistd.h>
#include <api/system.h>

int NE_get_unix_time(lua_State * lState){
	int current_time = (int) time(NULL);
	lua_pushnumber(lState, current_time);
	return 1;
}

int NE_get_sdl_ticks(lua_State * lState){
        int current_tick = SDL_GetTicks();
	lua_pushnumber(lState, current_tick);
	return 1;
}

int NE_get_time_since(lua_State * lState){
	const int start = (int) lua_tonumber(lState, 1);
	int passed = (int) time(NULL) - start;
	lua_pushnumber(lState, passed);
	return 1;
}

int NE_get_ticks_since(lua_State * lState){
	const int start = (int) lua_tonumber(lState, 1);
	int passed = SDL_GetTicks() - start;
	lua_pushnumber(lState, passed);
	return 1;
}

void api_register_system(lua_State * lState){
	lua_register(lState, "get_unix_time", NE_get_unix_time);
	lua_register(lState, "get_sdl_ticks", NE_get_sdl_ticks);
	lua_register(lState, "get_time_since", NE_get_time_since);
	lua_register(lState, "get_ticks_since", NE_get_ticks_since);
}