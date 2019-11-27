#
# Env variables
#

ENV_EMSCRIPTEN_FASTCOMP := /home/develop/emsdk/fastcomp/emscripten

#
# Default variables
#

# emscripten ...
TARGET_ENV ?= -
# debug, release ...
BUILD_ENV ?= -

#
# Compiler files
#

ifeq ($(TARGET_ENV),emscripten)
CC := $(ENV_EMSCRIPTEN_FASTCOMP)/em++
EXECUTABLE_C_FLAGS :=
C_FLAGS := --bind -Wno-dollar-in-identifier-extension
endif

ifeq ($(TARGET_ENV),-)
C_FLAGS := `sdl2-config --cflags --libs`
endif

CC ?= g++

EXECUTABLE_C_FLAGS ?= 
C_FLAGS += -std=c++17 -Wall -Wextra -pedantic -pedantic-errors

#c
# Project files
#
BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
WWW		:= www

LIBRARIES	:=

#
# Final exe file
#
ifeq ($(TARGET_ENV),emscripten)

EXECUTABLE  := $(WWW)/main.html

else

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
else
EXECUTABLE	:= main
endif

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
# Definition of build environement, choosing what target you want: release, debug, ... (not to be definied here but rather passed when executing the command make)
#
# BUILD_ENV=release

#
# Definition of makefile's working dirs 
# Specify an envionement to create the named speratee folder in the bin folder
#
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
.PHONY: all clean prep build

#
# Default build
#
all: build

#
# Build rules
#
build: prep ./$(BINARIES)/$(EXECUTABLE)

$(BINARIES)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(EXECUTABLE_C_FLAGS) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BINARIES)/%.o: $(SRC)/%.cpp
	@$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) -c $< -o $@ $(LIBRARIES)

$(BINARIES)/%.o: $(SRC)/%.cpp $(SRC)/%.hpp
	@$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) -c $< -o $@ $(LIBRARIES)

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

ifeq ($(TARGET_ENV),emscripten)

# Create dirs and recursively hardlink files
prep:
	mkdir -p $(BINARIES)
	mkdir -p $(BINARIES)/$(WWW)/
	ls ./$(WWW)/ | xargs -i rm -r -f ./$(BINARIES)/$(WWW)/{}
	ln -f ./$(WWW)/* ./$(BINARIES)/$(WWW)

serve: build
	cd ./$(BINARIES)/$(WWW) && python -m SimpleHTTPServer 8080

else
prep:
	mkdir -p $(BINARIES)
endif


run: all
	./$(BINARIES)/$(EXECUTABLE)

