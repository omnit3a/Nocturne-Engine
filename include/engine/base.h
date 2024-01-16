#ifndef ENGINE_BASE_H
#define ENGINE_BASE_H

#include <lua_headers.h>

void set_engine_no_warnings(int value);
void set_engine_no_errors(int value);

lua_State * engine_init(char * entry);

void engine_call_user_init(lua_State * lState);
void engine_call_user_render(lua_State * lState);
void engine_call_user_update(lua_State * lState, int rate);

#endif
