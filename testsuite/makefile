# Eduardo Ponce
# 10/2017
# Makefile for libsimdcpp-testsuite

# Compiler and linker options
CXXFLAGS +=

# Linker options
LFLAGS +=

# Preprocessor definitions
DEFINES +=

# Define header paths in addition to standard paths
INCDIR += -Iinclude

# Define library paths in addition to standard paths
LIBDIR +=

# Define libraries to link into executable
LIBS +=

# Header files
HEADERS += include/*.h

# Testsuite
OBJDIR := obj
SRC := src/test_simd.cpp src/test_utils.cpp
OBJ += $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))

DRIVER := src/test_suite.cpp
EXE := testsuite

#######################################

# Targets that are not real files
.PHONY: all clean

all: $(EXE)

$(EXE): $(DRIVER) $(OBJ)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) $< -o $@ $(OBJ) $(LIBS)

$(OBJDIR)/%.o: src/%.cpp $(HEADERS) $(MAKEFILE_LIST)
	@test ! -d $(OBJDIR) && mkdir $(OBJDIR) || true
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) -c $< -o $@ $(LIBS)

clean:
	@test -x $(EXE) && rm $(EXE) || true
	@test -d $(OBJDIR) && rm -r $(OBJDIR) || true

