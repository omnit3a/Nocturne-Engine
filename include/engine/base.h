#ifndef ENGINE_BASE_H
#define ENGINE_BASE_H

#include <lua_headers.h>

lua_State * engine_init(char * entry);
void engine_update(lua_State * lState);

void engine_call_user_init(lua_State * lState);
void engine_call_user_main(lua_State * lState);

#endif
