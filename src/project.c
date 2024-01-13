#include <frozen/frozen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <debug.h>
#include <project.h>

project_info_t project_load_info(void){
	project_info_t info;
	char * contents;

	if (!access(PROJECT_INFO_PATH, F_OK)){
		debug_loading_file_msg(PROJECT_INFO_PATH);
	} else {
		debug_file_notfound_error(PROJECT_INFO_PATH);
		exit(1);
	}
	
	info.name = NULL;
	info.author = NULL;
	info.short_description = NULL;
	info.version_string = NULL;
	info.version_id = -1;
	info.completeness = -1;
	
	contents = json_fread(PROJECT_INFO_PATH);
	json_scanf(contents, strlen(contents),
		   PROJECT_INFO_JSON_STRING,
		   &info.name,
		   &info.author,
		   &info.short_description,
		   &info.version_string,
		   &info.version_id,
		   &info.completeness);
	free(contents);
	
	if (info.name == NULL){
		debug_assign_null_error("Project name");
		exit(1);
	}

	if (info.author == NULL){
		debug_assign_null_error("Project author");
		exit(1);
	}

	if (info.short_description == NULL){
		debug_assign_null_error("Project description");
		exit(1);
	}

	if (info.version_string == NULL){
		debug_assign_null_error("Project version string");
		exit(1);
	}

	if (info.version_id < 0){
		debug_assign_range_error("Project version ID");
		exit(1);
	}

	if (info.completeness < 0 || info.completeness > 100){
		debug_assign_range_error("Project completeness");
		exit(1);
	}       
	
	return info;
}

void project_print_info(project_info_t info){
	printf("Project Info:\n");
	printf("\tName: %s\n", info.name);
	printf("\tAuthor: %s\n", info.author);
	printf("\tDescription: %s\n", info.short_description);
	printf("\tVersion: %s\n", info.version_string);
	printf("\tVersion ID: %d\n", info.version_id);
	printf("\tCompleteness: %.2f\n", info.completeness);
}
