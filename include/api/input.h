#ifndef API_INPUT_H
#define API_INPUT_H

#include <lua_headers.h>
#include <engine/sdl.h>

int NE_is_key_held(lua_State * lState);
int NE_is_left_mouse_held(lua_State * lState);
int NE_is_right_mouse_held(lua_State * lState);
int NE_get_mouse_x_distance(lua_State * lState);
int NE_get_mouse_y_distance(lua_State * lState);

void api_register_input(lua_State * lState);

#endif
