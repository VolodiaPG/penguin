EMSCRIPTEN_FASTCOMP ?= /home/vagrant/emsdk/fastcomp/emscripten

# default environement

# native env needs to be specified,
# otherwise it is the emscripten one that is used
ENV ?= emscripten

ifeq ($(ENV),native)
TARGET_EXEC ?= main
CXX := gcc
else
TARGET_EXEC ?= main.html
CXX := $(EMSCRIPTEN_FASTCOMP)/em++
endif





BUILD_DIR ?= ./bin
SRC_DIRS ?= ./src
WWW_DIRS ?= ./www
DOC_DIRS ?= ./doc

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++17 -Wall -Wextra -pedantic -pedantic-errors -Werror

ifeq ($(MODE),debug)
	CPPFLAGS += -O0 -g
else
	CPPFLAGS += -O3
endif

ifeq ($(ENV),emscripten)
	CPPFLAGS += -s ASSERTIONS=2 -s WASM=1
	EXECPPFLAGS := -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_main', '_initGame', '_deleteGame' ,'_play', '_mctsResult', '_checkStatus', '_getPlayerToPlay']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall']"
endif

TARGETCPPFLAGS ?= 

all: build

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(CPPFLAGS) $(EXECPPFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) -c $^ -o $@

#specific rules
build: $(BUILD_DIR)/$(TARGET_EXEC)


.PHONY: clean serve install

clean:
	$(RM) -r $(BUILD_DIR)

install:
	$(DOC_DIRS)/install.sh $(shell pwd)

serve:
	$(DOC_DIRS)/serve_nginx.sh

-include $(DEPS)

MKDIR_P ?= mkdir -p
