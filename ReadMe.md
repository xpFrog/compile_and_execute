Cande tries to be a replacement for Gnu Make. The executable for Cande is built using Cande itself. Instead of manually adding every source file Cande takes all files in the subfolders and compiles them into an exe and (optionally) executes it.

In the CandeConfig.ini are the instruction to the program. There are a few different variables in this file.
```ini
[CANDE_CONFIG]                   ;; This section HAS to be named exactly like this.
COMPILER=clang++                 ;; This is the compiler Cande will use when compiling the project.
COMPILER_FLAGS=-Wall -static -g  ;; These are the compiler flags the compiler will use.
COMPILER_INCLUDES=-Iinclude      ;; This is the include dirs Cande will compile with.
PROJECT_NAME=Cande.exe           ;; This is the name of the exe that is compiled.
FILE_TYPE=.cpp                   ;; This is the type of files Cande will look for in the dir.
```

Once you have this file in the root of the project you want to compile, open a terminal where this file is located and run
```powershell
Cande 
```
this will compile and execute the program. Optionally there are arguments you can pass to Cande like 
```powershell
-compile -execute -version
```
