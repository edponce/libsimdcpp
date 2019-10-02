# Eduardo Ponce
# 08/2019

# Defaults
TOPDIR ?= ../../
CXX ?= icpc
# SIMDFLAGS += -msse3 -mssse3 -msse4.1 -msse4.2
# SIMDFLAGS += -mavx
SIMDFLAGS += -mavx2
# SIMDFLAGS ?= -march=native -mtune=native
CXXFLAGS ?= $(SIMDFLAGS) -pedantic -Wall -Wextra -Wno-unknown-pragmas -O3 -std=c++11
LFLAGS ?= -funroll-loops -fopenmp
# LFLAGS ?= -funroll-loops -qopenmp

# Compiler and linker options
CXXFLAGS +=

# Linker options
LFLAGS +=

# Preprocessor definitions
DEFINES ?= -DSIMD_MODE
#DEFINES ?= -DSIMD_MMX
#DEFINES ?= -DSIMD_SSE2
# DEFINES ?= -DSIMD_SSE4_2
#DEFINES ?= -DSIMD_AVX
#DEFINES ?= -DSIMD_AVX2
#DEFINES ?= -DSIMD_AVX512

DEFINES += -DDEBUG

# Define header paths in addition to standard paths
INCDIR ?= -I$(TOPDIR)/include -I$(TOPDIR)/utils

# Define library paths in addition to standard paths
LIBDIR +=

# Define libraries to link into executable
LIBS +=

# Header files
HEADERS +=

# SIMD library
OBJ ?= $(TOPDIR)/obj/*.o

# Example
OBJDIR := obj
SRC :=
OBJ += $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))

DRIVER := gemv.cpp
BIN := gemv

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
