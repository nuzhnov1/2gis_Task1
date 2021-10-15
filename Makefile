# Variable definitions
MKDIR	= mkdir -p
RMDIR 	= rm -rf
COPY	= cp

PROG	= tsp
MAN		= manual.txt

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
.PHONY: build rebuild clean

# Build target
build: $(EXE) $(MAN)
	$(info Building a program is complete. Executable file is located in \
		"$(BIN)" directory.)

# Rebuild target
rebuild: clean build

# Clean target
clean:
	$(info Removing a directories "$(OBJ)" and "$(BIN)"...)
	$(RMDIR) $(OBJ) $(BIN)

# Creating directories target
$(BIN) $(OBJ):
	$(info Creating a directories "$(OBJ)" and "$(BIN)"...)
	$(MKDIR) $@

# Compilation target
$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	$(info Compiling a "$<" file...)
	$(CC) $(CFLAGS) -c $< -o $@

# Linkage target copying manual target
$(EXE): $(OBJS) | $(BIN)
	for item in $^ ; do \
		echo "Linking a $$item file..." ; \
	done
	$(CC) $^ -o $@
	$(info Copy the manual file "$(MAN)" to folder "$(BIN)"...)
	$(COPY) $(MAN) $(BIN)/$(MAN)
