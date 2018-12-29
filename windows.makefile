BUILD_DIR = ./build
TARGET = $(BUILD_DIR)/a.exe
OBJ_DIR = $(BUILD_DIR)
SRC = src

SOURCES = $(wildcard *.cpp $(SRC)/**/*.cpp)
NODIR = $(notdir $(SOURCES))
OBJECTS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(NODIR))

LIB = 
INCLUDES = C:/Users/jwang284/"OneDrive - Schlumberger"/virtualM/tools/boost_1_68_0/boost_1_68_0
CPPFLAGS = -Wall -Wextra -std=gnu++17 -c -ggdb3 -fexceptions -mthreads -W
MKDIR = mkdir -p

MAIN = $(SRC)/main.cpp
MAIN_OBJ = $(BUILD_DIR)/main.o


all: $(BUILD_DIR) $(TARGET)
# all: 
# 	@echo $(SOURCES)
# 	@echo $(notdir $(SOURCES))
# 	@echo $(OBJECTS)
# 	@echo $(dir $(SOURCES))

$(MAIN_OBJ): $(MAIN)
	g++ $(CPPFLAGS) -I $(INCLUDES) $< -o $@ 

$(BUILD_DIR):
	$(MKDIR) $@

$(TARGET): $(OBJECTS) $(MAIN_OBJ)
	@echo linking...
	g++ $^ -o $@
	@echo ok...

$(OBJECTS): $(SOURCES) 
	@$(MKDIR) $(dir $(SOURCES))
	g++ $(CPPFLAGS) -I $(INCLUDES) $< -o $@ 
	
clean: FORCE
	rm -f build/*.o 
	rm -f build/*.exe
	@echo ok..
FORCE: