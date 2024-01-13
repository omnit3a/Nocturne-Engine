#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <debug.h>
#include <engine/sdl.h>

void engine_init_SDL2(void){
	int status;

	status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (status < 0){
	        debug_sdl_init_failed_error();
		exit(1);
	}
}

engine_window_t engine_create_window(char * title, int width, int height){
	const Uint32 flags = SDL_WINDOW_RESIZABLE;
	engine_window_t window;
	
	window.window = SDL_CreateWindow(title, 0, 0, width, height, flags);
	
	if (window.window == NULL){
		debug_sdl_window_failed_error();
		SDL_Quit();
		exit(1);
	}
	
	window.x_pos = 0;
	window.y_pos = 0;
	window.width = width;
	window.height = height;
	
	return window;
}

engine_render_context_t engine_create_render_context(engine_window_t * window){
	const Uint32 flags = SDL_RENDERER_PRESENTVSYNC;
	engine_render_context_t context = {0};

	memcpy(&context.window, &window, sizeof(engine_window_t *));
	
	context.renderer = SDL_CreateRenderer(context.window->window, -1, flags);
	if (context.renderer == NULL){
	        debug_sdl_renderer_failed_error();
		SDL_Quit();
		exit(1);
	}

	SDL_RenderSetLogicalSize(context.renderer, window->width, window->height);	
	
	context.surface = SDL_GetWindowSurface(context.window->window);
	if (context.surface == NULL){
		debug_sdl_surface_failed_error();
		SDL_Quit();
		exit(1);
	}

	SDL_UpdateWindowSurface(context.window->window);

	return context;
}

void engine_destroy_render_context(engine_render_context_t * context){
	SDL_DestroyWindowSurface(context->window->window);
	SDL_DestroyWindow(context->window->window);
	SDL_DestroyRenderer(context->renderer);
	SDL_Quit();
}
