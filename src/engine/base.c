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
	api_register_input(lState);
	luaL_loadfile(lState, "main.lua");
	lua_pcall(lState, 0, 0, 0);
	
	return lState;
}

void engine_call_user_init(lua_State * lState){
	lua_getglobal(lState, "init");
	lua_pcall(lState, 0, 0, 0);
}

void engine_call_user_main(lua_State * lState){
	lua_getglobal(lState, "main");
	lua_pcall(lState, 0, 0, 0);
}
