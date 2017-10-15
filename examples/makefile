# Eduardo Ponce
# 10/2017
# Makefile for libsimdcpp

# Get name of makefile
MKFILE := $(MAKEFILE_LIST)

# C++ compiler
CXX := g++
#CXX := icpc
#CXX := clang++-4.0

# GNU/Intel SIMD extensions
# -mmx, -msse, -msse2, -msse3, -mssse3, -msse4.1, -msse4.2, -msse4
# -mavx, -mavx2, -mavx512bw, -mavx512f, -mavx512pf, -mavx512er, -mavx512cd
#SIMDFLAGS := -msse4.1
#SIMDFLAGS := -mavx2

# GNU compiler and linker options
CXXFLAGS := $(SIMDFLAGS) -march=native -mtune=native -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -std=c++98 -funroll-loops

# Intel compiler and linker options
#CXXFLAGS := $(SIMDFLAGS) -march=native -mtune=native -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -std=c++98 -funroll-loops

# Linker options
LFLAGS :=

# Preprocessor definitions
# SIMD modes: -DSIMD_MODE (auto), -DSSE4_1_VEC, -DAVX2_VEC, -DAVX512BW_VEC
# -DDEBUG
DEFINES := -DSIMD_MODE
#DEFINES := -DSSE4_1_VEC
#DEFINES := -DAVX2_VEC
#DEFINES := -DAVX512_VEC
DEFINES += -D_POSIX_C_SOURCE=200112L -D_ISOC99_SOURCE

# Define header paths in addition to standard paths
INCDIR := -I../include

# Define library paths in addition to standard paths
LIBDIR :=

# Define libraries to link into executable
LIBS := -lm

# Header files
HEADERS := ../include/*.h

# SIMD library
OBJ := ../obj/*.o

# Examples
DRIVER := driver.cpp
EXE := example

#######################################

# Targets that are not real files
.PHONY: all clean

all: $(EXE)

$(EXE): $(DRIVER) $(OBJ) $(HEADERS) $(MKFILE)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) $< -o $@ $(OBJ) $(LIBS)

clean:
	@test -x $(EXE) && rm $(EXE) || true

