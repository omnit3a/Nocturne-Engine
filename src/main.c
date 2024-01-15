#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <lua_headers.h>
#include <debug.h>
#include <engine/sdl.h>
#include <engine/base.h>
#include <api/graphics.h>
#include <cmd.h>

int main(int argc, char ** argv){	
	lua_State * lState;

        parse_cmd_args(argc, argv);
	
	lState = engine_init("main.lua");

	engine_call_user_init(lState);
	engine_call_user_main(lState);

	lua_close(lState);
	return 0;
}
