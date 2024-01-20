#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <debug.h>
#include <lua_headers.h>
#include <engine/sdl.h>
#include <engine/base.h>
#include <api/headers.h>

int engine_no_warnings = 0;
int engine_no_errors = 0;

void set_engine_no_warnings(int value){
	engine_no_warnings = value;
}

void set_engine_no_errors(int value){
	engine_no_errors = value;
}

lua_State * engine_init(char * entry){
	lua_State * lState;
	
	lState = luaL_newstate();
	luaL_openlibs(lState);
	api_register_graphics(lState);
	api_register_input(lState);
	api_register_math(lState);
	api_register_system(lState);
	luaL_loadfile(lState, "main.lua");
	lua_pcall(lState, 0, 0, 0);
	
	return lState;
}

int does_function_exist(lua_State * lState, char * function_name){
	lua_getglobal(lState, function_name);
        return lua_isfunction(lState, lua_gettop(lState));
}

void engine_call_user_init(lua_State * lState){
	if (!does_function_exist(lState, "init")){
		debug_function_notfound_error("init()");
		exit(1);
	}
	
	lua_getglobal(lState, "init");
	lua_pcall(lState, 0, 0, 0);
}

void engine_call_user_update(lua_State * lState, int rate){
	if (rate < 11){
		rate = 11;
	}
        double target_fps = 1000 / rate;
        double last_step = SDL_GetPerformanceCounter();
	
	lua_getglobal(lState, "update");
	if (!lua_isfunction(lState, lua_gettop(lState))){
	        debug_function_notfound_error("update()");
		exit(1);
	}

	while (1) {
		double current_time = SDL_GetPerformanceCounter();

		lua_getglobal(lState, "update");
		lua_pcall(lState, 0, 0, 0);

		double delta = (last_step - current_time);
		current_time = delta;
		delta /= (double)SDL_GetPerformanceCounter();
		delta *= 1000;
		SDL_Delay(floor(target_fps - delta));
	}
}

void engine_call_user_close(lua_State * lState){
	lua_getglobal(lState, "close");
	if (!lua_isfunction(lState, lua_gettop(lState))){
	        debug_function_notfound_error("close()");
		exit(1);
	}
	lua_pcall(lState, 0, 0, 0);
}