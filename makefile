# Eduardo Ponce
# 10/2017
# Makefile for libsimdcpp

# NOTE: paths or file names cannot have whitespaces.

# Get name of makefile and top directoryd
MAKEFILE := $(abspath $(lastword $(MAKEFILE_LIST)))
export TOPDIR := $(strip $(patsubst %/, %, $(dir $(MAKEFILE))))

# C++ compilers
# g++: 5.4.0
# icpc: ?
# clang++: 4.0
export CXX := g++
#export CXX := icpc
#export CXX := clang++-4.0

# GNU/Intel SIMD extensions
# -mmmx
# -msse, -msse2
# -msse3, -mssse3, -msse4.1, -msse4.2
# -mavx
# -mavx2
# -mavx512f, -mavx512bw, -mavx512dq, -mavx512fp, -mavx512cd, -mavx512er, -mavx512vl
# -mfma
#SIMDFLAGS += -mmmx
#SIMDFLAGS += -msse -msse2
#SIMDFLAGS += -msse3 -mssse3 -msse4.1 -msse4.2
#SIMDFLAGS += -mavx
#SIMDFLAGS += -mavx2
#SIMDFLAGS += -mavx512f -mavx512bw -mavx512dq
#SIMDFLAGS += -mfma
export SIMDFLAGS

# GNU compiler and linker options
export CXXFLAGS := $(SIMDFLAGS) -march=native -mtune=native -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -std=c++98 -funroll-loops
#export CXXFLAGS := $(SIMDFLAGS) -m32 -mtune=native -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -std=c++98 -funroll-loops

# Intel compiler and linker options
#export CXXFLAGS := $(SIMDFLAGS) -march=native -mtune=native -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -std=c++98 -funroll-loops

# Clang compiler and linker options
#export CXXFLAGS := $(SIMDFLAGS) -march=native -mtune=native -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -std=c++98 -funroll-loops

# Linker options
export LFLAGS :=

# Preprocessor definitions
# SIMD modes: -DSIMD_MODE (auto)
#             -DSIMD_MMX
#             -DSIMD_SSE2
#             -DSIMD_SSE4_2
#             -DSIMD_AVX
#             -DSIMD_AVX2
#             -DSIMD_AVX512
DEFINES := -DSIMD_MODE
#DEFINES := -DSIMD_MMX
#DEFINES := -DSIMD_SSE2
#DEFINES := -DSIMD_SSE4_2
#DEFINES := -DSIMD_AVX
#DEFINES := -DSIMD_AVX2
#DEFINES := -DSIMD_AVX512

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
# In many cases, errors could be resolved by setting _XOPEN_SOURCE appropriately.
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
export INCDIR := -I$(TOPDIR)/include

# Define library paths in addition to standard paths
export LIBDIR :=

# Define libraries to link into executable
export LIBS :=

# Header files
export HEADERS := $(TOPDIR)/include/*.h

# SIMD library
OBJDIR := $(TOPDIR)/obj
SRC := src/environ.cpp
export OBJ := $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))

# Testsuite
TESTDIR := testsuite

# Examples
EXAMPLEDIR := examples

# Benchmarks
BENCHMARKDIR := benchmarks

#######################################

# Targets that are not real files
.PHONY: all clean simd clean_tests clean_examples clean_all

all: simd testsuite examples benchmarks

# SIMD library
simd: $(OBJ)

$(OBJDIR)/%.o: src/%.cpp $(HEADERS) $(MAKEFILE)
	@test ! -d $(OBJDIR) && mkdir $(OBJDIR) || true
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) -c $< -o $@ $(LIBS)

clean:
	@test -d $(OBJDIR) && rm -r $(OBJDIR) || true

# Tests
testsuite: $(OBJ) $(HEADERS) $(MAKEFILE)
	$(MAKE) -C $(TESTDIR)

clean_tests:
	$(MAKE) -C $(TESTDIR) clean

# Examples
examples: $(OBJ) $(HEADERS) $(MAKEFILE)
	$(MAKE) -C $(EXAMPLEDIR)

clean_examples:
	$(MAKE) -C $(EXAMPLEDIR) clean

# Benchmarks
benchmarks: $(OBJ) $(HEADERS) $(MAKEFILE)
	$(MAKE) -C $(BENCHMARKDIR)

clean_benchmarks:
	$(MAKE) -C $(BENCHMARKDIR) clean

clean_all: clean clean_tests clean_examples clean_benchmarks

# Force
force:
	$(MAKE) clean
	$(MAKE)

force_tests:
	$(MAKE) clean_tests
	$(MAKE) testsuite

force_examples:
	$(MAKE) clean_examples
	$(MAKE) examples

force_benchmarks:
	$(MAKE) clean_benchmarks
	$(MAKE) benchmarks

force_all:
	$(MAKE) clean_all
	$(MAKE)

