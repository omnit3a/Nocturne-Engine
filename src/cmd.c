#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <getopt.h>
#include <string.h>
#include <debug.h>
#include <project.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <incbin/incbin.h>
#include <cmd.h>

INCTXT(InfoJson, "src/default-project/nproj/info.json");
INCTXT_EXTERN(InfoJson);
INCTXT(MainLua, "src/default-project/main.lua");
INCTXT_EXTERN(MainLua);
INCTXT(Credits, "CREDITS.txt");
INCTXT_EXTERN(Credits);

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
		{"credits",     no_argument,            0,      'c'},
		{"dir",		required_argument,	0,	'd'},
		{"init",        required_argument,      0,      'n'}
	};

	int dir_status;
	char arg[255];
	
	while (1){
		int index = 0;
		int opt = getopt_long(argc, argv, "viwecd:n:",
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
			strncpy(arg, optarg, 255);
		        dir_status = chdir(arg);
			if (dir_status < 0){
				debug_dir_notfound_error(arg);
				exit(1);
				break;
			}
			strncpy(result.working_dir, arg, 255);			
			printf("%s\n", result.working_dir);
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

		case 'c':
			printf("%s\n", gCreditsData);
			exit(0);
			
		case 'n':
			strncpy(arg, optarg, 255);
			dir_status = chdir(arg);

			DIR * nproj = opendir("nproj");
			struct dirent * next_file;
			char file_path[255*2];
			dir_status = nproj != NULL;			
			if (dir_status){

				while ((next_file = readdir(nproj)) != NULL){
					sprintf(file_path, "nproj/%s", next_file->d_name);
					remove(file_path);
				}
				closedir(nproj);

				dir_status = rmdir("nproj");
				if (dir_status < 0){
					debug_dir_notremove_error("nproj");
					exit(1);
				}
			}

			if (access("main.lua", F_OK) == 0){
				remove("main.lua");
				if (access("main.lua", F_OK) == 0){
					debug_file_notremove_error("main.lua");
					exit(1);
				}
			}

			char current_dir[255];
			getcwd(current_dir, 255);
			strncpy(current_dir, basename(current_dir), 255);
			if (strcmp(current_dir, "nproj") != 0){
				mkdir("nproj", 0b0111111111);
			}
			
			FILE * fp;
			fp = fopen("nproj/info.json", "w");
			if (fp == NULL){
				debug_file_notfound_error("nproj/info.json");
				exit(1);
			}
			fprintf(fp, "%s", gInfoJsonData);
			fclose(fp);

			fp = fopen("main.lua", "w");
			if (fp == NULL){
				debug_file_notfound_error("main.lua");
				exit(1);
			}
			fprintf(fp, "%s", gMainLuaData);
			fclose(fp);
			debug_init_project_msg(current_dir);
			exit(0);
			
		case '?':
			break;

		default:
			debug_invalid_option_error();
			exit(1);
		}
	}
	
	return result;
}