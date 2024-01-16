#ifndef API_SYSTEM_H
#define API_SYSTEM_H

int NE_get_unix_time(lua_State * lState);
int NE_get_sdl_ticks(lua_State * lState);
int NE_get_time_since(lua_State * lState);
int NE_get_ticks_since(lua_State * lState);

void api_register_system(lua_State * lState);

#endif