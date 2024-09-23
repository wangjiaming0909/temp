CC = g++
FLAGS = -std=c++17 -c  -ggdb -Wfatal-errors -fexceptions -O0
DEFS = 
DEFINES = $(patsubst %, -D%, $(DEFS))

SOURCE_DIR = ./src
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj

MKDIR = mkdir -p
RM = rm -rf

SOURCES = $(shell find $(SOURCE_DIR) -type f -name '*.cpp')
LEET_HDRS = $(shell find $(SOURCE_DIR) -type f -name '*.h')
OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES) )

TARGET = $(BUILD_DIR)/a.out
LIB = /usr/lib
INCLUDES = /usr/include

LD_FLAGS = -pthread

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -L $(LIB) $(LD_FLAGS) -o $@
	@echo "OK...."

$(BUILD_DIR):
	$(MKDIR) $@

$(OBJECTS): $(OBJ_DIR)/%.o : $(SOURCE_DIR)/%.cpp $(LEET_HDRS)
	$(MKDIR) $(dir $@)
	$(CC) $(DEFINES) $(FLAGS) $< -I $(INCLUDES) -o $@

clean: FORCE
	$(RM) $(OBJECTS) $(TARGET)
FORCE:
