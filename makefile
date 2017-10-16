# Eduardo Ponce
# 10/2017
# Makefile for libsimdcpp

# Get name of makefile and top directory (paths or files cannot have whitespaces)
export MKFILE := $(abspath $(lastword $(MAKEFILE_LIST)))
export TOPDIR := $(dir $(MKFILE))

# C++ compiler
CXX := g++
#CXX := icpc
#CXX := clang++-4.0
export CXX

# GNU/Intel SIMD extensions
# -mmx
# -msse, -msse2, -msse3, -mssse3, -msse4.1, -msse4.2
# -mavx, -mavx2
# -mavx512bw, -mavx512f, -mavx512pf, -mavx512er, -mavx512cd
# -mfma
#SIMDFLAGS := -mmx
#SIMDFLAGS := -msse4.2
#SIMDFLAGS := -mavx
#SIMDFLAGS := -mavx2
#SIMDFLAGS += -mfma
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

# Feature Test Macros
# _POSIX_SOURCE: (deprecated)
# _POSIX_C_SOURCE: POSIX series of standards
# _XOPEN_SOURCE/_XOPEN_SOURCE_EXTENDED: X/Open Unix standards
# _LARGEFILE_SOURCE: Enable large files
# _LARGEFILE64_SOURCE: Enable large files in 64-bits
# _FILE_OFFSET_BITS: Enable 64-bit file offset
# _ISOC99_SOURCE: ISO C standard
# _GNU_SOURCE: ISO C89, ISO C99, POSIX.1, POSIX.2, BSD, SVID, X/Open, LFS, and GNU extensions
# _DEFAULT_SOURCE : POSIX 2008, BSD and SVID features
# _REENTRANT/_THREAD_SAFE : POSIX.1c/pthreads
#
# Most of the errors, most of the times, could be resolved by setting _XOPEN_SOURCE appropriately.
#
# _XOPEN_SOURCE < 500
#    is same as _POSIX_C_SOURCE = 2.
# 500 <= _XOPEN_SOURCE < 600
#    is same as _POSIX_C_SOURCE = 199506L.
# 600 <= _XOPEN_SOURCE < 700
#    is same as _POSIX_C_SOURCE = 200112L.
# 700 <= _XOPEN_SOURCE (since glibc 2.10)
#    is same as _POSIX_C_SOURCE = 200809L.
# _XOPEN_SOURCE >= 500
#    is same as defining _XOPEN_SOURCE_EXTENDED
#DEFINES += -D_XOPEN_SOURCE=700
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
#OBJ := $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))
OBJ := $($(notdir $(SRC)):.cpp=.o)

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

