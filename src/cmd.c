#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <debug.h>
#include <project.h>
#include <unistd.h>
#include <cmd.h>

cmd_options_t parse_cmd_args(int argc, char ** argv){
        cmd_options_t result;
	result.no_warnings = 0;
	result.no_errors = 0;
	strcpy(result.working_dir, ".");
	struct option long_options[] = {
		{"version",	no_argument,		0,	'v'},
		{"info",	no_argument,		0,	'i'},
		{"no-warnings", no_argument,		0,	'w'},
		{"no-errors",	no_argument,		0,	'e'},
		{"dir",		required_argument,	0,	'd'}
	};

	while (1){
		int index = 0;
		int opt = getopt_long(argc, argv, "vd:iwe",
				      long_options, &index);

		if (opt == -1){
			break;
		}

		switch (opt){
		case 'v':
			printf("Runtime version: %s\n",
			       CMD_ENGINE_VERSION);
		        exit(0);
			
		case 'd':
			char arg[255];
			int dir_status;
			strncpy(arg, optarg, 255);
		        dir_status = chdir(arg);
			if (dir_status < 0){
				debug_dir_notfound_error(arg);
				exit(1);
				break;
			}			
			strncpy(result.working_dir, arg, 255);			
			break;
			
		case 'i':
			if (access(PROJECT_INFO_PATH, F_OK) != 0){
				debug_file_notfound_error(PROJECT_INFO_PATH);
				exit(1);
			}
		        project_info_t proj_info = project_load_info();
			project_print_info(proj_info);
			exit(0);
			break;
			
		case 'w':
			result.no_warnings = 1;
			set_debug_no_warnings();
			break;
			
		case 'e':
			result.no_errors = 1;
			set_debug_no_errors();
			break;

		case '?':
			break;

		default:
			debug_invalid_option_error();
			exit(1);
		}
	}
	
	return result;
}