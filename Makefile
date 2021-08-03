CPP_FILES=$(wildcard src/*.cpp)
RC_FILES=$(wildcard res/*.rc)
OBJ_FILES=$(subst .cpp,.o, $(CPP_FILES)) $(subst .rc,.o, $(RC_FILES))
COMPILED_FLAGS=-pedantic -W -Wall -O3

LINKED_FLAGS=-s
#-static-libgcc -static-libstdc++

# (.h)
INCLUDE_DIRECTORIES=-I./include

# (.a .dll)
LIB_DIRECTORIES=-L./lib

LIB_FILES=-lopenal32 -lsfml-system -lsfml-graphics -lsfml-window

.PHONY: all clean %.o build cleanobj run

all: clean %.o build cleanobj run

build: $(OBJ_FILES)
	g++ $^ -o $@ $(LIB_DIRECTORIES) $(LIB_FILES) 
#$(LINKED_FLAGS)

%.o: %.cpp
	g++ -g -c $^ -o $@ $(INCLUDE_DIRECTORIES) $(COMPILED_FLAGS)

%.o: %.rc
	windres $^ -o $@ $(INCLUDE_DIRECTORIES)

run:
	build.exe

clean:
	del *.o *.exe /s

cleanobj:
	del *.o /s