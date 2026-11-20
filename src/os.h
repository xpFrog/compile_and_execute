#pragma once 

#include <string>
#include <vector>
#ifdef _WIN32
#include "dirent.h"
#define GetCurrentDir _getcwd
#define IS_WINDOWS 1
#else
#include <dirent.h>
#include <unistd.h>
#define GetCurrentDir getcwd
#define IS_WINDOWS 0
#endif


std::string get_exec_path(void);
std::vector<std::string> GetAllFilesWithExtensionInExecFolder(std::string file_ext);