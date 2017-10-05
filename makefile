# Eduardo Ponce
# 10/2017
# Makefile for libsimdcpp

# Get name of makefile
MKFILE := $(MAKEFILE_LIST)

# C++ compiler
CXX := g++
#CXX := icpc

# GNU/Intel SIMD extensions
# -mmx, -msse, -msse2, -msse3, -mssse3, -msse4.1, -msse4.2, -msse4
# -mavx, -mavx2, -mavx512bw, -mavx512f, -mavx512pf, -mavx512er, -mavx512cd
#SIMDFLAG := -msse4.1
#SIMDFLAG := -mavx2

# GNU compiler and linker options
CXXFLAGS := $(SIMDFLAG) -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -march=native -std=c++98 -funroll-loops

# Intel compiler and linker options
#CXXFLAGS := $(SIMDFLAG) -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -O3 -march=native -std=c++98 -funroll-loops

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
INCDIR := -Iinclude -Itestsuite/include

# Define library paths in addition to standard paths
LIBDIR :=

# Define libraries to link into executable
LIBS := -lm

# Header files
HEADERS := include/*.h testsuite/include/*.h

# Testsuite
TOPDIR := testsuite
OBJDIR := $(TOPDIR)/obj
SRC := $(TOPDIR)/src/test_simd.cpp $(TOPDIR)/src/test_utils.cpp
OBJ := $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))
DRIVER := $(TOPDIR)/src/test_suite.cpp

#######################################

# Targets that are not real files
.PHONY: all clean

all: testsuite

testsuite : $(OBJ) $(DRIVER)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) $(DRIVER) -o $(TOPDIR)/$@ $(OBJ) $(LIBS)

$(OBJDIR)/%.o: $(TOPDIR)/src/%.cpp $(HEADERS) $(MKFILE)
	@test ! -d $(OBJDIR) && mkdir $(OBJDIR) || true
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) -c $< -o $@ $(LIBS)

clean:
	@test -x $(TOPDIR)/testsuite && rm $(TOPDIR)/testsuite || true
	@test -d $(OBJDIR) && rm -r $(OBJDIR) || true

