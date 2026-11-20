#pragma once 

#include <string>
#include <vector>
#ifdef _WIN32
#include "../include/dirent.h"
#else
#include <dirent.h>
#endif


std::string get_exec_path(void);
std::vector<std::string> GetAllFilesWithExtensionInExecFolder(std::string file_ext);