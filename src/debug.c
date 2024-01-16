#include <stdio.h>
#include <stdlib.h>
#include <debug.h>

int no_warnings = 0;
int no_errors = 0;

void set_debug_no_warnings(void){
	no_warnings = 1;
}

void set_debug_no_errors(void){
	no_errors = 1;
}

/* General error messages */
void debug_arg_amount_error(int expected_args){
	if (no_errors){
		return;
	}
	fprintf(stderr, "args: Incorrect amount of arguments, expected %d\n",
		expected_args);
}

void debug_invalid_option_error(void){
	if (no_errors){
		return;
	}
	fprintf(stderr, "engine-runtime: Invalid option\n");
}

void debug_dir_notfound_error(char * path){
	if (no_errors){
		return;
	}
	fprintf(stderr, "%s: Directory not found\n", path);
}

void debug_file_notfound_error(char * path){
	if (no_errors){
		return;
	}
	fprintf(stderr, "%s: File not found\n", path);
}

void debug_assign_null_error(char * assignee_name){
	if (no_errors){
		return;
	}
	fprintf(stderr, "%s: Incorrectly assigned as NULL\n", assignee_name);
}

void debug_assign_range_error(char * assignee_name){
	if (no_errors){
		return;
	}
	fprintf(stderr, "%s: Value assigned is not within correct range\n",
		assignee_name);
}

void debug_dir_notremove_error(char * path){
	if (no_errors){
		return;
	}
	fprintf(stderr, "%s: Directory could not be removed\n", path);
}

void debug_file_notremove_error(char * path){
	if (no_errors){
		return;
	}
	fprintf(stderr, "%s: File could not be removed\n", path);
}

/* Rendering related error messages */
void debug_sdl_init_failed_error(void){
	if (no_errors){
		return;
	}
	fprintf(stderr, "SDL2: Failed to initialize\n");
}

void debug_sdl_window_failed_error(void){
	if (no_errors){
		return;
	}
	fprintf(stderr, "SDL2: Failed to create window\n");
}

void debug_sdl_renderer_failed_error(void){
	if (no_errors){
		return;
	}
	fprintf(stderr, "SDL2: Failed to create renderer\n");
}

void debug_sdl_surface_failed_error(void){
	if (no_errors){
		return;
	}
	fprintf(stderr, "SDL2: Failed to create surface\n");
}

/* Status messages */
void debug_loading_file_msg(char * path){
	if (no_warnings){
		return;
	}
        fprintf(stdout, "%s: Loading file...\n", path);
}

void debug_init_project_msg(char * path){
	if (no_warnings){
		return;
	}
	fprintf(stdout, "%s: Initialized default project\n", path);
}