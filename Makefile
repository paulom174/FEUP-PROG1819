# Executable name
PROG := exec

# Project folders
SRC_DIR := .
INC_DIR := .
OBJ_DIR := ./obj

# Compiler
CC := g++

# Compiler flags
CFLAGS := -I$(INC_DIR)
CFLAGSW := #-Wall -Wextra -Werror

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Compile source into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CFLAGSW) -c -o $@ $<

# Link object files into executable file
$(PROG): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(CFLAGSW) -o $@ $^


# GNUMake feature: Prevent confusing with files called all, clean or run
.PHONY: all clean run

all: $(PROG)

clean:
	rm -f $(PROG)
	rm -r -f $(OBJ_DIR)

run: all
	./$(PROG)