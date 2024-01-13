#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <lua_headers.h>
#include <engine/sdl.h>
#include <api/graphics.h>

engine_render_context_t main_render_context;

int NE_init_renderer(lua_State * lState){
	engine_init_SDL2();
	return 0;
}

int NE_create_window(lua_State * lState){
        const char * title = lua_tostring(lState, 1);
        const int width = (int) lua_tonumber(lState, 2);
        const int height = (int) lua_tonumber(lState, 3);
	engine_window_t window;

	window = engine_create_window((char *)title, width, height);
        main_render_context = engine_create_render_context(&window);

	return 0;
}

int NE_redraw_window(lua_State * lState){	
	SDL_RenderPresent(main_render_context.renderer);
	SDL_SetRenderDrawColor(main_render_context.renderer, 0, 0, 0, 255);
	SDL_RenderClear(main_render_context.renderer);
	return 0;
}

int NE_load_bmp(lua_State * lState){
	const char * path = lua_tostring(lState, 1);
	const int texture_id = (int) lua_tonumber(lState, 2);
	
	engine_register_texture(&main_render_context, (char *)path, texture_id);
	lua_pushnumber(lState, texture_id);
	return 1;
}

int NE_draw_texture(lua_State * lState){
	const int texture_id = (int) lua_tonumber(lState, 1);
	engine_texture_t texture;
	
	texture = engine_get_texture(texture_id);
	SDL_Rect target = {
		texture.x,
		texture.y,
		texture.width,
		texture.height
	};
	SDL_RenderCopy(main_render_context.renderer, texture.texture, NULL, &target);
	return 0;
}

int NE_reshape_texture(lua_State * lState){
	const int texture_id = (int) lua_tonumber(lState, 1);
	const int x = (int) lua_tonumber(lState, 2);
	const int y = (int) lua_tonumber(lState, 3);
	const int w = (int) lua_tonumber(lState, 4);
	const int h = (int) lua_tonumber(lState, 5);

	engine_reshape_texture(texture_id, x, y, w, h);
	return 0;
}

void api_register_graphics(lua_State * lState){
	lua_register(lState, "init_renderer", NE_init_renderer);
	lua_register(lState, "create_window", NE_create_window);
	lua_register(lState, "redraw_window", NE_redraw_window);
	lua_register(lState, "load_bmp", NE_load_bmp);
	lua_register(lState, "draw_texture", NE_draw_texture);
	lua_register(lState, "reshape_texture", NE_reshape_texture);
}

engine_render_context_t api_get_render_context(void){
	return main_render_context;
}
