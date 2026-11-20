CC = g++#x86_64-w64-mingw32-g++

CCFLAGS = -Wall -g -static#-static-libgcc -static-libstdc++

TARGET = Cande.exe
TARGET_DEL = Cande.exe

SRCS = \
src/main.cpp \
src/process_args.cpp \
src/os.cpp \
src/cande.cpp

OBJS = $(SRCS:.c=.o)

INCLUDES = -Iinclude

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(INCLUDES) $(CCFLAGS) -o $(TARGET) $(OBJS) 

#clean:
#rm -f $(TARGET_DEL) $(OBJS)