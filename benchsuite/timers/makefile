# Eduardo Ponce
# 11/2017
# Makefile for timers

# C compilers
CC := gcc

# Compiler and linker options
CFLAGS +=

# Linker options
LFLAGS +=

# Preprocessor definitions
#DEFINES := -DUSE_MONOTONIC_CLOCK
DEFINES +=

# Define header paths in addition to standard paths
INCDIR := -Iinclude

# Define library paths in addition to standard paths
LIBDIR :=

# Define libraries to link into executable
LIBS :=

# Header files
HEADERS := include/timers.h

# Example
OBJDIR := obj
SRC := src/timers.cpp
OBJ := $(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SRC)))

DRIVER := timer_example.cpp
EXE := timer_example

#######################################

# Targets that are not real files
.PHONY: all clean

all: $(OBJ)

$(EXE): $(DRIVER) $(OBJ) $(HEADERS) $(MAKEFILE_LIST)
	$(CC) $(CFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) $< -o $@ $(OBJ) $(LIBS)

$(OBJDIR)/%.o: src/%.cpp $(HEADERS) $(MAKEFILE_LIST)
	@test ! -d $(OBJDIR) && mkdir $(OBJDIR) || true
	$(CC) $(CFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) -c $< -o $@ $(LIBS)

clean:
	rm -f $(EXE)
	rm -rf $(OBJDIR)

