EMSCRIPTEN_PATH ?= /emsdk/upstream/emscripten

# default environement

# native env needs to be specified,
# otherwise it is the emscripten one that is used
ENV ?= emscripten

ifeq ($(ENV),native)
TARGET_EXEC ?= main
CXX := g++
else
TARGET_EXEC ?= main.js
CXX := $(EMSCRIPTEN_PATH)/em++
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
#-Wcast-align -Wover-aligned
CPPFLAGS := $(INC_FLAGS) -std=c++17 -Wall -Wextra -pedantic -pedantic-errors -Werror -Wcast-align

ifeq ($(ENV),emscripten)
	# -s MODULARIZE=1 to wrap the code in a module, easier to consume in our angular app
	CPPFLAGS += --bind -s WASM=1
	EXECPPFLAGS :=
endif

ifeq ($(MODE),debug)
	CPPFLAGS += -O0 -g
ifeq ($(ENV),emscripten)
	CPPFLAGS += -s STACK_OVERFLOW_CHECK=2 -s ASSERTIONS=2 -s DEMANGLE_SUPPORT=1 -s SAFE_HEAP=1 -s WARN_UNALIGNED=1
endif
else
	CPPFLAGS += -O3
endif

all: build

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CPPFLAGS) $(EXECPPFLAGS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp %.hpp
	$(MKDIR_P) $(dir $@)
	$(CXX) -c $< $(CPPFLAGS) -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) -c $< $(CPPFLAGS) -o $@

#specific rules
build: $(BUILD_DIR)/$(TARGET_EXEC)

.PHONY: clean serve

clean:
	$(RM) -r $(BUILD_DIR)

serve:
	$(DOC_DIRS)/serve_nginx.sh

-include $(DEPS)

MKDIR_P ?= mkdir -p
