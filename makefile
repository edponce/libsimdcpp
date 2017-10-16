# Eduardo Ponce
# 10/2017
# Makefile for libsimdcpp

# Get name of makefile
MKFILE := $(MAKEFILE_LIST)

# C++ compiler
CXX := g++
#CXX := icpc
#CXX := clang++-4.0
export CXX

# GNU/Intel SIMD extensions
# -mmx, -msse, -msse2, -msse3, -mssse3, -msse4.1, -msse4.2, -msse4
# -mavx, -mavx2, -mavx512bw, -mavx512f, -mavx512pf, -mavx512er, -mavx512cd
SIMDFLAGS :=
#SIMDFLAGS := -msse4.1
#SIMDFLAGS := -mavx2
export SIMDFLAGS

# GNU compiler and linker options
CXXFLAGS := $(SIMDFLAGS) -march=native -mtune=native -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -std=c++98 -funroll-loops

# Intel compiler and linker options
#CXXFLAGS := $(SIMDFLAGS) -march=native -mtune=native -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -std=c++98 -funroll-loops

# Clang compiler and linker options
#CXXFLAGS := $(SIMDFLAGS) -march=native -mtune=native -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -std=c++98 -funroll-loops
export CXXFLAGS

# Linker options
LFLAGS :=
export LFLAGS

# Preprocessor definitions
# SIMD modes: -DSIMD_MODE (auto), -DSSE4_1_VEC, -DAVX2_VEC, -DAVX512BW_VEC
# -DDEBUG
DEFINES := -DSIMD_MODE
#DEFINES := -DSSE4_1_VEC
#DEFINES := -DAVX2_VEC
#DEFINES := -DAVX512_VEC
DEFINES += -D_POSIX_C_SOURCE=200112L -D_ISOC99_SOURCE
export DEFINES

# Define header paths in addition to standard paths
INCDIR := -Iinclude

# Define library paths in addition to standard paths
LIBDIR :=

# Define libraries to link into executable
LIBS :=

# Header files
HEADERS := include/*.h

# SIMD library
OBJDIR := obj
SRC := src/environ.cpp
OBJ := $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))

# Testsuite
TESTDIR := testsuite

# Examples
EXAMPLEDIR := examples

#######################################

# Targets that are not real files
.PHONY: all clean simd clean_tests clean_examples clean_all

all: simd testsuite examples

# SIMD library
simd: $(OBJ)

$(OBJDIR)/%.o: src/%.cpp $(HEADERS) $(MKFILE)
	@test ! -d $(OBJDIR) && mkdir $(OBJDIR) || true
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) -c $< -o $@ $(LIBS)

clean:
	@test -d $(OBJDIR) && rm -r $(OBJDIR) || true

# Tests
testsuite: $(OBJ) $(HEADERS) $(MKFILE)
	$(MAKE) -C $(TESTDIR)

clean_tests:
	$(MAKE) -C $(TESTDIR) clean

# Examples
examples: $(OBJ) $(HEADERS) $(MKFILE)
	$(MAKE) -C $(EXAMPLEDIR)

clean_examples:
	$(MAKE) -C $(EXAMPLEDIR) clean

clean_all: clean clean_tests clean_examples

