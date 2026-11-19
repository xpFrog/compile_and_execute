#pragma once
#include "SimpleIni.h"
#include <string>

typedef struct  {
      std::string Compiler;
      std::string CompilerFlags;
      std::string CompilerIncludes;
      std::string ProjectName;
      std::string FileEndingType;
} CandeConfig;

int process_args(int arg_count,char *args[]);
void execute_args(int arg_id);

void compile(CandeConfig *ccfg);
void execute(CandeConfig *ccfg);

bool TryGetCandeConfig(CandeConfig *ccfg);
bool IsIniValueNull(CSimpleIniA* ini, const char* section, const char* valueName);