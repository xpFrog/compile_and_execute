Cande tries to be a replacement for Gnu Make. Cande itself is built using Cande. Instead of manually adding every source file Cande takes all files in the subfolders and compiles them into a exe and (optionally) executes it.

In the CandeConfig.ini are the instruction to the program. There are a few different variables in this file.

Everything here is in the **[CANDE_CONFIG]** section.

![#1589F0]**COMPILER=clang++**`#1589F0 # This is the compiler Cande will use when compiling the project.\
**COMPILER_FLAGS=-Wall -static -g** # These are the compiler flags the compiler will use.\
**COMPILER_INCLUDES=-Iinclude** # This is the include dirs Cande will compile with.\
**PROJECT_NAME=Cande.exe** # This is the name of the exe that is compiled.\
**FILE_TYPE=.cpp** # This is the type of files Cande will look for in the dir.

A finished **CandeConfig.ini** file should look like this. (These can be in any order.)\
**[CANDE_CONFIG]**\
**COMPILER=clang++**\
**COMPILER_FLAGS=-Wall -static -g**\
**COMPILER_INCLUDES=-Iinclude**\
**PROJECT_NAME=Cande.exe**\
**FILE_TYPE=.cpp**

Once you have this file in the directory you want to compile a project with open a terminal and run **Cande**. This will compile and execute the program. Optionally there are arguments you can pass to Cande like **-compile**, **-execute** and **-version**.
