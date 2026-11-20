#pragma once 

#include <string>
#include <vector>
#define WINDOWS
#ifdef WINDOWS
#include "../include/dirent.h"
#else
#include <dirent.h>
#endif


std::string get_exec_path(void);
void list_all_sub_dir(void);
int parse_ext(const struct dirent *dir);
std::vector<std::string> get_all_files_with_extension_in_exec_folder(std::string file_ext);