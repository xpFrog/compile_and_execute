#pragma once 

#include <string>
#include <vector>
#ifdef _WIN32
#include <direct.h>
#define GET_CURRENT_DIR _getcwd
#define IS_WINDOWS 1
#else
#include <unistd.h>
#define GET_CURRENT_DIR getcwd
#define IS_WINDOWS 0
#endif


std::string get_exec_path(void);
std::vector<std::string> GetAllFilesWithExtensionInExecFolder(std::string file_ext);