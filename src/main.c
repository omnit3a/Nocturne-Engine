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
	DIR * working_dir;
	lua_State * lState;
	if (argc < 2){
		debug_arg_amount_error(2);
		exit(1);
	}

	working_dir = opendir(argv[1]);
	if (working_dir){
		chdir(argv[1]);
		closedir(working_dir);
	} else {
		debug_dir_notfound_error(argv[1]);
		exit(1);
	}

	lState = engine_init("main.lua");

	engine_call_user_init(lState);
	while (1){
		engine_call_user_update(lState);
	}
	
	return 0;
}
