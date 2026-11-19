#include "process_args.h"
#include <cstdio>
#include <cstdlib>
#include <shellapi.h>
#include <string.h>
#include <string>
#include <vector>
#include <winuser.h>
#include "SimpleIni.h"
#include "stringh.h"
#include "os.h"
#include "cande.h"
#include <windows.h>


#define CANDE_CONFIGURATION_FAILED_TO_FETCH_FROM_INI "Failed to load \"CandeConfig.ini\" please create this file!\n"
#define CANDE_FAILED_TO_FETCH_INI_VALUE "Failed to fetch \"%s\" in CandeConfig.ini\n"

enum ARG_TYPE {
      COMPILE_ARG         = 0,
      EXECUTE_ARG         = 1,
      COMP_AND_EXEC_ARG   = 2,
      VERSION_ARG         = 3,
      LIST_CPP_ARG        = 4,
};

// Processes the arguments passed from the main function.
int process_args(int arg_count,char *args[]) {
      for (int i = 0; i < arg_count; ++i) {
            if (strcmp(args[i], "-compile" ) == STRING_EQUAL)       { return COMPILE_ARG;             }
            if (strcmp(args[i], "-execute" ) == STRING_EQUAL)       { return EXECUTE_ARG;             }
            if (strcmp(args[i], "-version" ) == STRING_EQUAL)       { return VERSION_ARG;             }
            if (strcmp(args[i], "-listcpp" ) == STRING_EQUAL)       { return LIST_CPP_ARG;            }
      }

      // If nothing is passed to cande the default behaviour should be to compile and execute.
      
      return COMP_AND_EXEC_ARG;
}

// Executes the argument that was given to the "process_args" function.
void execute_args(int arg_id) {

      if (arg_id == VERSION_ARG) {
            printf("The current version of Cande is %s\n", get_cande_version());
      }

      CandeConfig ccfg;
      if (!TryGetCandeConfig(&ccfg)) { return; }

      if (arg_id == LIST_CPP_ARG) {
            std::vector<std::string> files(get_all_files_with_extension_in_exec_folder(ccfg.FileEndingType.c_str()));
            for (auto &f : files) {
                  printf("%s\n", f.c_str());
            }
      }

      if (arg_id == COMPILE_ARG) {
            compile(&ccfg);
      }
      
      if (arg_id == EXECUTE_ARG) {
            execute(&ccfg);
      }

      if (arg_id == COMP_AND_EXEC_ARG) {
            compile(&ccfg);
            execute(&ccfg);
      }
}

void compile(CandeConfig *ccfg) {
      std::string compile_cmd("");

      // Add compiler to compile command
      compile_cmd.append(ccfg->Compiler + " ");

      // Add compiler args
      compile_cmd.append(ccfg->CompilerFlags + " ");

      // Add includes
      compile_cmd.append(ccfg->CompilerIncludes + " ");

      // Add output to compile command
      compile_cmd.append("-o " + ccfg->ProjectName + " ");

      // Add files to compile command.
      std::vector<std::string> files(get_all_files_with_extension_in_exec_folder(".cpp"));
      for (auto &fn : files) {
            compile_cmd.append(fn + " ");
      }

      // Execute the compiler using the command we just created.
      printf("%s\n", compile_cmd.c_str());
      system(compile_cmd.c_str());
      printf("Compiled executable to \"%s/%s\"\n", get_exec_path().c_str(), ccfg->ProjectName.c_str());
}     

void execute(CandeConfig *ccfg) {

      std::string exec_command_string;
      exec_command_string.append("start /WAIT /B ");
      exec_command_string.append(ccfg->ProjectName);
      printf("Executed %s\n", exec_command_string.c_str());
      system(exec_command_string.c_str());
}

bool TryGetCandeConfig(CandeConfig *ccfg) {
      std::string iniLoadPath = get_exec_path();
      iniLoadPath.append(CANDE_CONFIG_FILE_NAME);

      CSimpleIniA ini;
	SI_Error rc = ini.LoadFile(iniLoadPath.c_str());
	if (rc < 0) { 
            printf(CANDE_CONFIGURATION_FAILED_TO_FETCH_FROM_INI);
            return false;
      };

      if (!IsIniValueNull(&ini, "CANDE_CONFIG", "COMPILER")) {
            ccfg->Compiler = ini.GetValue("CANDE_CONFIG", "COMPILER"); 
      } else {
            return false;
      }

      if (!IsIniValueNull(&ini, "CANDE_CONFIG", "COMPILER_FLAGS")) {
            ccfg->CompilerFlags = ini.GetValue("CANDE_CONFIG", "COMPILER_FLAGS"); 
      } else {
            return false;
      }

      if (!IsIniValueNull(&ini, "CANDE_CONFIG", "COMPILER_INCLUDES")) {
            ccfg->CompilerIncludes = ini.GetValue("CANDE_CONFIG", "COMPILER_INCLUDES"); 
      } else {
            return false;
      }

      if (!IsIniValueNull(&ini, "CANDE_CONFIG", "PROJECT_NAME")) {
            ccfg->ProjectName = ini.GetValue("CANDE_CONFIG", "PROJECT_NAME"); 
      } else {
            return false;
      }

      if (!IsIniValueNull(&ini, "CANDE_CONFIG", "FILE_TYPE")) {
            ccfg->FileEndingType = ini.GetValue("CANDE_CONFIG", "FILE_TYPE"); 
      } else {
            return false;
      }
 
      return true;
}

bool IsIniValueNull(CSimpleIniA* ini, const char* section, const char* valueName) {
      const char* value_v;
      value_v = ini->GetValue(section, valueName);
      if (value_v == nullptr) {
            printf(CANDE_FAILED_TO_FETCH_INI_VALUE, valueName);
            return true;
      } else {
            return false;
      }
}