#ifndef PROJECT_H
#define PROJECT_H

/*
  all project metadata and config files are stored in the nproj
  directory within the root of the project tree
*/
#define PROJECT_INFO_PATH "nproj/info.json"

typedef struct project_info_s {
	char * name;
	char * author;
	char * short_description;
        char * version_string;
	int version_id;
	float completeness;
} project_info_t;

#define PROJECT_INFO_JSON_STRING "{name: %Q,\
                        author: %Q,			\
			short_description: %Q,		\
			version_string: %Q,		\
			version_id: %d,			\
			completeness: %f}"

project_info_t project_load_info(void);
void project_print_info(project_info_t info);

#endif
