# Eduardo Ponce
# 11/2017
# Makefile for libsimdcpp

# NOTE: paths or file names cannot have whitespaces.

# Get name of makefile and top directory
MAKEFILE := $(abspath $(lastword $(MAKEFILE_LIST)))
export TOPDIR := $(strip $(patsubst %/, %, $(dir $(MAKEFILE))))

# C++ compilers
# g++: 5.4.0
# icpc: ?
# clang++: 4.0
export CXX := g++
# export CXX := icpc
# export CXX := clang++-4.0
# export CXX := powerpc64-linux-gnu-g++-5

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
SIMDFLAGS += -msse3 -mssse3 -msse4.1 -msse4.2
#SIMDFLAGS += -xsse3 -xssse3 -xsse4.1 -xsse4.2
#SIMDFLAGS += -mavx
#SIMDFLAGS += -mavx2
#SIMDFLAGS += -march=skylake-avx512
#SIMDFLAGS += -mavx512f -mavx512bw -mavx512dq
#SIMDFLAGS += -mfma
#SIMDFLAGS += -xMIC-AVX512
#SIMDFLAGS += -march=native -mtune=native
export SIMDFLAGS

# Compiler and linker options
ifeq ($(CXX),g++) # GNU
export CXXFLAGS := $(SIMDFLAGS) -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -ftree-vectorize -std=c++98
#export CXXFLAGS += -fopt-info

else ifneq (,$(findstring clang,$(CXX))) # Clang
export CXXFLAGS := $(SIMDFLAGS) -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -std=c++98
#export CXXFLAGS += -fopt-info

else ifeq ($(CXX),icpc) # Intel
export CXXFLAGS := $(SIMDFLAGS) -pedantic -Wall -Wextra -Wno-unknown-pragmas -O3 -std=c++98
#export CXXFLAGS += -qopt-report=4 -qopt-report-phase ipo

else ifneq (,$(findstring powerpc,$(CXX))) # IBM/GNU PowerPC
export CXXFLAGS := $(SIMDFLAGS) -mpowerpc64 -maltivec -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -std=c++98
endif

# Linker options
ifeq ($(CXX),g++) # GNU
export LFLAGS += -funroll-loops
export LFLAGS += -fopenmp

else ifneq (,$(findstring clang,$(CXX))) # Clang
export LFLAGS += -funroll-loops
export LFLAGS += -fopenmp=libomp

else ifeq ($(CXX),icpc) # Intel
export LFLAGS += -funroll-loops
export LFLAGS += -qopenmp
#export LFLAGS += -fopenmp

else ifneq (,$(findstring powerpc,$(CXX))) # IBM/GNU PowerPC
export LFLAGS += -fopenmp
endif

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
#export LIBDIR := -L$(TOPDIR)/somelibrary
export LIBDIR :=

# Define libraries to link into executable
export LIBS :=

# Header files
export HEADERS := $(TOPDIR)/include/*.h $(TOPDIR)/utils/*.h

# SIMD library
OBJDIR := $(TOPDIR)/obj
SRC := src/environ.cpp utils/utils.cpp utils/vutils.cpp
export OBJ := $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))

# Testsuite
TESTSUITEDIR := testsuite

# Examples
EXAMPLEDIR := examples
EXAMPLES := hello_world small_gemv

# Benchmarks
BENCHMARKDIR := benchmarks

# Benchsuite
BENCHSUITEDIR := benchsuite

#######################################

# Targets that get executed even if files of those names exist
.PHONY: all clean simd clean_testsuite clean_example clean_benchmark clean_all doc

all: simd testsuite #example #benchmark

# SIMD library
simd: $(OBJ)

$(OBJDIR)/%.o: src/%.cpp $(HEADERS) $(MAKEFILE)
	@test ! -d $(OBJDIR) && mkdir $(OBJDIR) || true
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) -c $< -o $@ $(LIBS)

$(OBJDIR)/%.o: utils/%.cpp $(HEADERS) $(MAKEFILE)
	@test ! -d $(OBJDIR) && mkdir $(OBJDIR) || true
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) -c $< -o $@ $(LIBS)

clean:
	rm -rf $(OBJDIR)

# Testsuite
testsuite: simd
	$(MAKE) -C $(TESTSUITEDIR)

clean_testsuite:
	$(MAKE) -C $(TESTSUITEDIR) clean

# Examples
example: simd
	@for dir in $(addprefix $(EXAMPLEDIR)/,$(EXAMPLES)); do \
		$(MAKE) -C $$dir; \
	done

clean_example:
	@for dir in $(addprefix $(EXAMPLEDIR)/,$(EXAMPLES)); do \
		$(MAKE) -C $$dir clean; \
	done

# Benchmarks
benchmark: simd
	$(MAKE) -C $(BENCHMARKDIR)

clean_benchmark:
	$(MAKE) -C $(BENCHMARKDIR) clean

# Benchsuite
benchsuite: simd
	$(MAKE) -C $(BENCHSUITEDIR)

clean_benchsuite:
	$(MAKE) -C $(BENCHSUITEDIR) clean

clean_all: clean clean_testsuite clean_example clean_benchmark

doc:
	doxygen Doxyfile
