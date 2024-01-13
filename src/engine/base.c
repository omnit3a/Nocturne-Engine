#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <lua_headers.h>
#include <engine/sdl.h>
#include <engine/base.h>
#include <api/headers.h>

lua_State * engine_init(char * entry){
	lua_State * lState;
	
	lState = luaL_newstate();
	luaL_openlibs(lState);
	api_register_graphics(lState);
	luaL_loadfile(lState, "main.lua");
	lua_pcall(lState, 0, 0, 0);
	
	return lState;
}

void engine_call_user_init(lua_State * lState){
	lua_getglobal(lState, "init");
	lua_pcall(lState, 0, 0, 0);
}

uint32_t last_frame = 0;
void engine_call_user_update(lua_State * lState){
	uint32_t current_frame;
	uint32_t delta;

	current_frame = SDL_GetTicks();
	delta = current_frame - last_frame;

	if (delta > ENGINE_FRAME_RATE){
		last_frame = current_frame;
		
		lua_getglobal(lState, "update");
		lua_pcall(lState, 0, 0, 0);
	}
}
