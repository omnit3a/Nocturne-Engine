#ifndef API_SYSTEM_H
#define API_SYSTEM_H

#include <lua_headers.h>

void set_system_no_warnings(int value);
void set_system_no_errors(int value);

int NE_get_unix_time(lua_State * lState);
int NE_get_sdl_ticks(lua_State * lState);
int NE_get_time_since(lua_State * lState);
int NE_get_ticks_since(lua_State * lState);
int NE_print_warning(lua_State * lState);
int NE_print_error(lua_State * lState);
int NE_wait_millis(lua_State * lState);

void api_register_system(lua_State * lState);

#endif