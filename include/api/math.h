#ifndef API_MATH_H
#define API_MATH_H

#include <lua_headers.h>

int NE_set_math_seed(lua_State * lState);
int NE_set_math_seed_time(lua_State * lState);
int NE_get_math_seed(lua_State * lState);
int NE_get_random(lua_State * lState);
int NE_get_random_range(lua_State * lState);

void api_register_math(lua_State * lState);

#endif