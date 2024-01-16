#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <lua_headers.h>
#include <time.h>
#include <unistd.h>
#include <api/system.h>

int system_no_warnings = 0;
int system_no_errors = 0;

void set_system_no_warnings(int value){
	system_no_warnings = value;
}

void set_system_no_errors(int value){
	system_no_errors = value;
}

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

int NE_print_warning(lua_State * lState){
	if (system_no_warnings){
		return 0;
	}	
	const char * string = lua_tostring(lState, 1);
        printf("[WARNING]: %s\n", string);
	return 0;
}

int NE_print_error(lua_State * lState){
	if (system_no_errors){
		return 0;
	}
	const char * string = lua_tostring(lState, 1);
	fprintf(stderr, "[ERROR]: %s\n", string);
	return 0;
}

int NE_wait_millis(lua_State * lState){
	const int millis = (int) lua_tonumber(lState, 1);
	SDL_Delay(millis);
	return 0;
}

void api_register_system(lua_State * lState){
	lua_register(lState, "get_unix_time", NE_get_unix_time);
	lua_register(lState, "get_sdl_ticks", NE_get_sdl_ticks);
	lua_register(lState, "get_time_since", NE_get_time_since);
	lua_register(lState, "get_ticks_since", NE_get_ticks_since);
	lua_register(lState, "print_warning", NE_print_warning);
	lua_register(lState, "print_error", NE_print_error);
	lua_register(lState, "wait_millis", NE_wait_millis);
}