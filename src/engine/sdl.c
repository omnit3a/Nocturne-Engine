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
	const Uint32 flags = 0;
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

	SDL_SetRenderDrawColor(context.renderer, 0, 0, 0, 255);
	SDL_RenderSetLogicalSize(context.renderer, window->width, window->height);	

	context.surface = SDL_GetWindowSurface(context.window->window);

	if (context.surface == NULL){
		debug_sdl_surface_failed_error();
		SDL_Quit();
		exit(1);
	}

	context.texture = SDL_CreateTextureFromSurface(context.renderer, context.surface);
	SDL_UpdateWindowSurface(context.window->window);
	
	return context;
}

void engine_destroy_render_context(engine_render_context_t * context){
	engine_free_textures();
	SDL_DestroyTexture(context->texture);
	SDL_FreeSurface(context->surface);
	SDL_DestroyRenderer(context->renderer);
	SDL_DestroyWindow(context->window->window);
	SDL_Quit();
}

engine_texture_t * textures;
int texture_count = 1;

void engine_register_texture(engine_render_context_t * context, char * path, int id){
	if (textures == NULL){
	        textures = malloc(sizeof(engine_texture_t));
	}
	textures[texture_count - 1].surface = SDL_LoadBMP(path);
	textures[texture_count - 1].texture = SDL_CreateTextureFromSurface(context->renderer,
									   textures[texture_count - 1].surface);
	
	textures[texture_count - 1].x = 0;
	textures[texture_count - 1].y = 0;
	textures[texture_count - 1].width = 0;
	textures[texture_count - 1].height = 0;
	textures[texture_count - 1].texture_id = id;
	textures = realloc(textures, sizeof(engine_texture_t) * texture_count * 2);
	texture_count += 1;
}

void engine_free_textures(void){
	if (textures == NULL){
		return;

	}
	for (int n = 0 ; n < texture_count-1 ; n++){
		if (textures[n].texture != NULL){
			SDL_DestroyTexture(textures[n].texture);
		}
		if (textures[n].surface != NULL){
			SDL_FreeSurface(textures[n].surface);
		}
	}

	free(textures);
}

engine_texture_t engine_get_texture(int id){
	for (int texture = 0 ; texture < texture_count ; texture++){
		if (textures[texture].texture_id == id){
			return textures[texture];
		}
	}
	return (engine_texture_t){0};
}

void engine_reshape_texture(int id, int x, int y, int w, int h){
	for (int texture = 0 ; texture < texture_count ; texture++){
		if (textures[texture].texture_id == id){
			textures[texture].x = x;
			textures[texture].y = y;
			textures[texture].width = w;
			textures[texture].height = h;
			return;
		}
	}	
}
