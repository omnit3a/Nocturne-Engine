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

int NE_destroy_window(lua_State * lState){
	engine_destroy_render_context(&main_render_context);
	return 0;
}

int NE_draw_pixel(lua_State * lState){
	const int x = (int) lua_tonumber(lState, 1);
        const int y = (int) lua_tonumber(lState, 2);
	const int red = (int) lua_tonumber(lState, 3);
        const int green = (int) lua_tonumber(lState, 4);
	const int blue = (int) lua_tonumber(lState, 5);

	SDL_SetRenderDrawColor(main_render_context.renderer, red, green, blue, 255);
	SDL_RenderDrawPoint(main_render_context.renderer, x, y);
	return 0;
}

void api_register_graphics(lua_State * lState){
	lua_register(lState, "init_renderer", NE_init_renderer);
	lua_register(lState, "create_window", NE_create_window);
	lua_register(lState, "redraw_window", NE_redraw_window);
	lua_register(lState, "destroy_window", NE_destroy_window);
	lua_register(lState, "draw_pixel", NE_draw_pixel);
}

engine_render_context_t api_get_render_context(void){
	return main_render_context;
}
