#ifndef ENGINE_SDL_H
#define ENGINE_SDL_H

#include <SDL2/SDL.h>

#define ENGINE_FRAME_RATE 1000/60.0

typedef struct engine_window_s {
	int x_pos;
	int y_pos;
	int width;
	int height;
	SDL_Window * window;
} engine_window_t;

typedef struct engine_render_context_s {
	engine_window_t * window;
	SDL_Renderer * renderer;
	SDL_Surface * surface;	
} engine_render_context_t;

void engine_init_SDL2(void);
engine_window_t engine_create_window(char * title, int width, int height);
engine_render_context_t engine_create_render_context(engine_window_t * window);
void engine_destroy_render_context(engine_render_context_t * context);

#endif
