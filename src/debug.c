#include <stdio.h>
#include <stdlib.h>
#include <debug.h>

/* General error messages */
void debug_arg_amount_error(int expected_args){
	fprintf(stderr, "args: Incorrect amount of arguments, expected %d\n",
		expected_args);
}

void debug_dir_notfound_error(char * path){
	fprintf(stderr, "%s: Directory not found\n", path);
}

void debug_file_notfound_error(char * path){
	fprintf(stderr, "%s: File not found\n", path);
}

void debug_assign_null_error(char * assignee_name){
	fprintf(stderr, "%s: Incorrectly assigned as NULL\n", assignee_name);
}

void debug_assign_range_error(char * assignee_name){
	fprintf(stderr, "%s: Value assigned is not within correct range\n",
		assignee_name);
}

/* Rendering related error messages */
void debug_sdl_init_failed_error(void){
	fprintf(stderr, "SDL2: Failed to initialize\n");
}

void debug_sdl_window_failed_error(void){
	fprintf(stderr, "SDL2: Failed to create window\n");
}

void debug_sdl_renderer_failed_error(void){
	fprintf(stderr, "SDL2: Failed to create renderer\n");
}

void debug_sdl_surface_failed_error(void){
	fprintf(stderr, "SDL2: Failed to create surface\n");
}

/* Status messages */
void debug_loading_file_msg(char * path){
        printf("%s: Loading file...\n", path);
}
