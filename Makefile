EMSCRIPTEN_FASTCOMP ?= /emsdk/fastcomp/emscripten

# default environement

# native env needs to be specified,
# otherwise it is the emscripten one that is used
ENV ?= emscripten

ifeq ($(ENV),native)
TARGET_EXEC ?= main
CXX := g++
else
TARGET_EXEC ?= main.html
CXX := $(EMSCRIPTEN_FASTCOMP)/em++
endif

BUILD_DIR ?= ./bin
SRC_DIRS ?= ./src
WWW_DIRS ?= ./www
DOC_DIRS ?= ./doc

ifeq ($(ENV),emscripten)
	SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
else
	SRCS := $(shell find ./src -type f \( -iname "*.cpp" ! -iname "*.bind.cpp" \))
endif
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++17 -Wall -Wextra -pedantic -pedantic-errors -Werror
CPPFLAGS := $(INC_FLAGS) -std=c++17 -Wall -Wextra -pedantic -pedantic-errors -Werror -lstdc++

ifeq ($(MODE),debug)
	CPPFLAGS += -O0 -g
else
	CPPFLAGS += -O3
endif

ifeq ($(ENV),emscripten)
	CPPFLAGS += -s ASSERTIONS=2 -s WASM=1 --bind
	EXECPPFLAGS := 
endif

all: build

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(CPPFLAGS) $(EXECPPFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) -c $^ -o $@

#specific rules
build: $(BUILD_DIR)/$(TARGET_EXEC)

.PHONY: clean serve

clean:
	$(RM) -r $(BUILD_DIR)

serve:
	$(DOC_DIRS)/serve_nginx.sh

-include $(DEPS)

MKDIR_P ?= mkdir -p
