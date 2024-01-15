#ifndef CMD_H
#define CMD_H

#define CMD_ENGINE_VERSION "1.0.1"

typedef struct cmd_options_s {
	char working_dir[255];
	int no_warnings;
	int no_errors;
} cmd_options_t;

cmd_options_t parse_cmd_args(int argc, char ** argv);

#endif