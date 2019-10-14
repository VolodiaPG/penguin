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
RELC_FLAGS := -O3
REL_DIR    := release
REL_EXE    := ${REL_DIR}/$(EXECUTABLE)

#
# Debug build settings
#
DBGC_FLAGS := -g -O0
DBG_DIR    := debug
DBG_EXE    := ${DBG_DIR}/$(EXECUTABLE)

#
# Project files
#
BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=

#
# Commands that are phony (not files)
#
.PHONY: all clean debug release prep

#
# Default build
#
all: prep release

#
# Debug rules
#
debug: prep ./$(BIN)/$(DBG_EXE)

$(BIN)/$(DBG_EXE): $(SRC)/*
	$(CC) $(C_FLAGS) $(DBGC_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

dbg_run: debug
	./$(BIN)/$(DBG_EXE)

#
# Release rules
#
release: prep ./$(BIN)/$(REL_EXE)

$(BIN)/$(REL_EXE): $(SRC)/*
	$(CC) $(C_FLAGS) $(RELC_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

rel_run: release
	./$(BIN)/$(REL_EXE)

#
# Other rules
#
clean:
	$(RM) -r $(BIN)/*

prep:
	@mkdir -p $(BIN)/$(DBG_DIR) $(BIN)/$(REL_DIR)

run: all
	./$(BIN)/$(REL_EXE)

