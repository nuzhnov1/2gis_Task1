# Variable definitions
MKDIR	= mkdir -p
RMDIR 	= rm -rf
PROG	= tsp
CC 		= g++
BIN		= ./bin
OBJ		= ./obj
INCLUDE	= ./include
SRC		= ./src
SRCS	= $(wildcard $(SRC)/*.cpp)
OBJS	= $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))
EXE		= $(BIN)/$(PROG)
CFLAGS	= -I$(INCLUDE) -O3

# Phony targets
.PHONY: build clean rebuild

# Build target
build: $(EXE)
	$(info Building a program is complete. Executable file is located in \
		"$(BIN)" directory.)

# Clean target
clean:
	$(info Removing a directories "$(OBJ)" and "$(BIN)"...)
	$(RMDIR) $(OBJ) $(BIN)

# Rebuild target
rebuild: clean build

# Creating directories target
$(BIN) $(OBJ):
	$(info Creating a directories "$(OBJ)" and "$(BIN)"...)
	$(MKDIR) $@

# Compilation target
$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	$(info Compiling a "$<" file...)
	$(CC) $(CFLAGS) -c $< -o $@

# Linkage target
$(EXE): $(OBJS) | $(BIN)
	for item in $^ ; do \
		echo "Linking a $$item file..." ; \
	done
	$(CC) $^ -o $@
