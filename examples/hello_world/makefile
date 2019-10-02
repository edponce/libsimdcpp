# Eduardo Ponce
# 08/2019

# Defaults
TOPDIR ?= ../../
CXX ?= icpc
SIMDFLAGS ?= -march=native -mtune=native
CXXFLAGS ?= $(SIMDFLAGS) -pedantic -Wall -Wextra -Wno-unknown-pragmas -O3 -std=c++98
LFLAGS ?= -funroll-loops

# Compiler and linker options
CXXFLAGS +=

# Linker options
LFLAGS +=

# Preprocessor definitions
DEFINES ?= -DSIMD_MODE

# Define header paths in addition to standard paths
INCDIR ?= -I$(TOPDIR)/include

# Define library paths in addition to standard paths
LIBDIR +=

# Define libraries to link into executable
LIBS +=

# Header files
HEADERS +=

# SIMD library
OBJ ?= $(TOPDIR)/obj/environ.o

# Example
OBJDIR := obj
SRC :=
OBJ += $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))

DRIVER := example.cpp
BIN := example

#######################################

# Targets that are not real files
.PHONY: all clean

all: $(BIN)

$(BIN): $(DRIVER) $(OBJ) $(HEADERS) $(MAKEFILE_LIST)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) $< -o $@ $(OBJ) $(LIBS)

$(OBJDIR)/%.o: src/%.cpp $(HEADERS) $(MAKEFILE_LIST)
	@test ! -d $(OBJDIR) && mkdir $(OBJDIR) || true
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) -c $< -o $@ $(LIBS)

clean:
	rm -f $(BIN)
	rm -rf $(OBJDIR)
