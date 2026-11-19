#include "os.h"
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <cstdio>
#include <filesystem>
#include <vector>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

// TODO: Check on linux machine if it works there!
std::string get_exec_path(void) {
      return std::string(GetCurrentDir(NULL, 0));
}

std::vector<std::string> get_all_files_with_extension_in_exec_folder(std::string file_ext) {
      std::vector<std::string> files;
      std::string path(get_exec_path());
      for (auto &p : std::filesystem::recursive_directory_iterator(path)) {
            if (p.path().extension() == file_ext) {
                  std::string string_trimmed(p.path().string());
                  string_trimmed.erase(0, path.length() + 1); // I add 1 here for the "/" of the dir.
                  files.push_back(string_trimmed);
            }
      }

      return files;
}