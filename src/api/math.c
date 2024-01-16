#include <stdio.h>
#include <stdlib.h>
#include <lua_headers.h>
#include <time.h>
#include <api/math.h>

int math_seed = 0;

int NE_set_math_seed(lua_State * lState){
	math_seed = (int) lua_tonumber(lState, 1);
	srand(math_seed);
	return 0;
}

int NE_set_math_seed_time(lua_State * lState){
	math_seed = time(0);
	srand(math_seed);
	return 0;
}

int NE_get_math_seed(lua_State * lState){
	lua_pushnumber(lState, math_seed);
	return 1;
}

int NE_get_random(lua_State * lState){
	int value = rand();
	lua_pushnumber(lState, value);
	return 1;
}

int NE_get_random_range(lua_State * lState){
	const int min = (int) lua_tonumber(lState, 1);
	const int max = (int) lua_tonumber(lState, 2);
	int value = rand();
	value = value % (max + 1 - min) + min;
	lua_pushnumber(lState, value);
	return 1;
}

void api_register_math(lua_State * lState){
	lua_register(lState, "set_math_seed", NE_set_math_seed);
	lua_register(lState, "set_math_seed_time", NE_set_math_seed_time);
	lua_register(lState, "get_math_seed", NE_get_math_seed);
	lua_register(lState, "get_random", NE_get_random);
	lua_register(lState, "get_random_range", NE_get_random_range);
}
