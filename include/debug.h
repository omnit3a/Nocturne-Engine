#ifndef ENGINE_DEBUG_H
#define ENGINE_DEBUG_H

void set_debug_no_warnings(int value);
void set_debug_no_errors(int value);

void debug_arg_amount_error(int expected_args);
void debug_invalid_option_error(void);
void debug_dir_notfound_error(char * path);
void debug_file_notfound_error(char * path);
void debug_assign_null_error(char * assignee_name);
void debug_assign_range_error(char * assignee_name);
void debug_dir_notremove_error(char * path);
void debug_file_notremove_error(char * path);
void debug_function_notfound_error(char * function_name);

void debug_sdl_init_failed_error(void);
void debug_sdl_window_failed_error(void);
void debug_sdl_renderer_failed_error(void);
void debug_sdl_surface_failed_error(void);

void debug_loading_file_msg(char * path);
void debug_init_project_msg(char * path);

#endif
