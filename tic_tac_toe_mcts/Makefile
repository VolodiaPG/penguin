#
# Compiler files
#
CC		:= g++
C_FLAGS := -std=c++17 -Wall -Wextra `sdl2-config --cflags --libs`

#
# Exe file
#
ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
else
EXECUTABLE	:= main
endif

#
# Release build settings
#
release :C_FLAGS += -O3
REL_DIR    := release

#
# Debug build settings
#
debug :C_FLAGS += -g -O0
DBG_DIR    := debug

#
# Project files
#
BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=


#
# Definition of build environement, choosing what target you want: release, debug, ... (not to be definied here but rather passed when executing the command make)
#
# BUILD_ENV=release

#
# Definition of makefile's working dirs 
# Specify an envionement to create the named speratee folder in the bin folder
#
BUILD_ENV ?= -

ifneq ($(BUILD_ENV),-)
BINARIES := $(BIN)/$(BUILD_ENV)
endif

BINARIES ?= $(BIN)

#
# Objects
#
# $(wildcard $(SRC)/*.hpp) is replaced by a space-separated list of names of existing files that match one of the given file name patterns. 
# $(patsubst pattern,replacement,$(var))
OBJECTS := $(patsubst $(SRC)/%.cpp, $(BINARIES)/%.o, $(wildcard $(SRC)/*.cpp))

#
# Commands that are phony (not files)
#
.PHONY: all clean prep

#
# Default build
#
all: build

#
# Build rules
#
build: prep ./$(BINARIES)/$(EXECUTABLE)

$(BINARIES)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BINARIES)/%.o: $(SRC)/%.cpp
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) -c $< -o $@ $(LIBRARIES)

$(BINARIES)/%.o: $(SRC)/%.cpp $(SRC)/%.hpp
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) -c $< -o $@ $(LIBRARIES)

#
# Debug rules
#
debug: build

dbg_run: debug
	./$(BINARIES)/$(EXECUTABLE)

#
# Release rules
#
release: build

rel_run: release
	./$(BINARIES)/$(EXECUTABLE)

#
# Other rules
#
clean:
	$(RM) -r $(BIN)/*

prep:
	mkdir -p $(BINARIES)

run: all
	./$(BINARIES)/$(EXECUTABLE)

