#ifndef API_GRAPHICS_H
#define API_GRAPHICS_H

#include <lua_headers.h>
#include <engine/sdl.h>

int NE_init_renderer(lua_State * lState);
int NE_create_window(lua_State * lState);
int NE_redraw_window(lua_State * lState);
int NE_destroy_window(lua_State * lState);
int NE_draw_pixel(lua_State * lState);

void api_register_graphics(lua_State * lState);

engine_render_context_t api_get_render_context(void);

#endif
