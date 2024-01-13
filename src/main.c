#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <lua_headers.h>
#include <debug.h>
#include <engine/sdl.h>
#include <engine/base.h>
#include <api/graphics.h>

int main(int argc, char ** argv){	
	lua_State * lState;

	lState = engine_init("main.lua");

	engine_call_user_init(lState);
	engine_call_user_main(lState);

	lua_close(lState);
	return 0;
}
