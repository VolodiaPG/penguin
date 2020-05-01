EMSCRIPTEN_PATH ?= /emsdk/upstream/emscripten
DOXYGEN := doxygen
DOXYGEN_FLAGS := 

GREEN   := \033[1;32m

WHITE   := \033[0;m

NUMBER_PTHREADS_WORKERS := 4

# default environement

# native env needs to be specified,
# otherwise it is the emscripten one that is used
ENV ?= emscripten
MULTITHREADED ?= true

ifeq ($(ENV),native)
TARGET_EXEC ?= main
CXX := g++
else
TARGET_EXEC ?= main.html
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

LDFLAGS := -lpthread

# CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++17 -Wall -Wextra -pedantic -pedantic-errors -Werror
#-Wcast-align -Wover-aligned
CPPFLAGS := $(INC_FLAGS) -std=c++17 -Wall -Wextra -pedantic -pedantic-errors -Werror -Wcast-align -Wold-style-cast

ifeq ($(ENV),emscripten)
ifeq ($(MULTITHREADED),true)
	CPPFLAGS += -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=$(NUMBER_PTHREADS_WORKERS)
endif
	CPPFLAGS += --bind -s WASM=1
	EXECPPFLAGS := 
else
ifeq ($(MULTITHREADED),true)
	CPPFLAGS += -DNUMBER_THREADS=$(NUMBER_PTHREADS_WORKERS)
endif
endif

ifeq ($(MODE),debug)
	CPPFLAGS += -O0 -g
ifeq ($(ENV),emscripten)
	CPPFLAGS += -s STACK_OVERFLOW_CHECK=2 -s ASSERTIONS=2 -s DEMANGLE_SUPPORT=1 -s SAFE_HEAP=1 -s WARN_UNALIGNED=1
endif
else
	CPPFLAGS += -O3 -DNDEBUG
endif

all: build

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@$(CXX) $(OBJS) $(CPPFLAGS) $(EXECPPFLAGS) -o $@ $(LDFLAGS)
	@printf "\n[$(GREEN)OK$(WHITE)] Binary : $(TARGET_EXEC)\n"
	@echo "-------------------\n"

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CPPFLAGS) -c -o $@ $<
	@printf "[$(GREEN)OK$(WHITE)] $<\n"
# $(CXX) -c $< $(CPPFLAGS) -o $@ $<

#specific rules
build: $(BUILD_DIR)/$(TARGET_EXEC)

.PHONY: clean serve doc

doc:
	$(MKDIR_P) ./$(DOC_DIRS)/$(DOXYGEN) 
	$(RM) -r ./$(DOC_DIRS)/$(DOXYGEN)/*
	cd $(DOC_DIRS)/ && $(DOXYGEN) $(DOXYGEN_FLAGS)

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
