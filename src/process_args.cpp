#include "process_args.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "stringh.h"
#include "os.h"
#include "cande.h"


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
            return;
      }

      if (arg_id == LIST_CPP_ARG) {
            std::vector<std::string> files(GetAllFilesWithExtensionInExecFolder(".cpp"));
            for (auto &f : files) {
                  printf("%s\n", f.c_str());
            }
            return;
      }

      CandeConfig candeConfigFile;
      if (!TryGetCandeConfig(&candeConfigFile)) { return; }

      

      if (arg_id == COMPILE_ARG) {
            compile(&candeConfigFile);
            return;
      }
      
      if (arg_id == EXECUTE_ARG) {
            execute(&candeConfigFile);
            return;
      }

      if (arg_id == COMP_AND_EXEC_ARG) {
            compile(&candeConfigFile);
            execute(&candeConfigFile);
            return;
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
      std::vector<std::string> files(GetAllFilesWithExtensionInExecFolder(".cpp"));
      for (auto &fn : files) {
            compile_cmd.append(fn + " ");
      }

      // Execute the compiler using the command we just created.
      printf("%s\n", compile_cmd.c_str());
      system(compile_cmd.c_str());
      printf("Compiled executable to \"%s/%s\"\n", get_exec_path().c_str(), ccfg->ProjectName.c_str());
}     

void execute(CandeConfig *candeConfigFile) {

      std::string exec_command_string;
      if (IS_WINDOWS == 1) {
            exec_command_string.append("start /WAIT /B ");   
      } else {
            exec_command_string.append("./");   
      }
      
      exec_command_string.append(candeConfigFile->ProjectName);
      printf("Executed %s\n", exec_command_string.c_str());
      system(exec_command_string.c_str());
}

bool TryGetCandeConfig(CandeConfig *candeConfigFile) {
      std::string iniLoadPath = get_exec_path();
      iniLoadPath.append(CANDE_CONFIG_FILE_NAME);
      //printf("%s\n", iniLoadPath.c_str());


      CSimpleIniA ini;
	SI_Error rc = ini.LoadFile(iniLoadPath.c_str());
	if (rc < 0) { 
            printf(CANDE_CONFIGURATION_FAILED_TO_FETCH_FROM_INI);
            return false;
      };

      if (IsIniValueNull(&ini, "CANDE_CONFIG", "COMPILER")) {
            return false;
      } else {
            candeConfigFile->Compiler = ini.GetValue("CANDE_CONFIG", "COMPILER"); 
      }

      if (IsIniValueNull(&ini, "CANDE_CONFIG", "COMPILER_FLAGS")) {
            return false;
      } else {
            candeConfigFile->CompilerFlags = ini.GetValue("CANDE_CONFIG", "COMPILER_FLAGS"); 
      }

      if (IsIniValueNull(&ini, "CANDE_CONFIG", "COMPILER_INCLUDES")) {
            return false;
      } else {
            candeConfigFile->CompilerIncludes = ini.GetValue("CANDE_CONFIG", "COMPILER_INCLUDES"); 
      }

      if (IsIniValueNull(&ini, "CANDE_CONFIG", "PROJECT_NAME")) {
            return false;
      } else {
            candeConfigFile->ProjectName = ini.GetValue("CANDE_CONFIG", "PROJECT_NAME"); 
      }

      if (IsIniValueNull(&ini, "CANDE_CONFIG", "FILE_TYPE")) {
            return false;
      } else {
            candeConfigFile->FileEndingType = ini.GetValue("CANDE_CONFIG", "FILE_TYPE"); 
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