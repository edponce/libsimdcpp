# Eduardo Ponce
# 10/2017
# Makefile for libsimdcpp-testsuite

# Define header paths in addition to standard paths
INCDIR := -I$(TOPDIR)/include -Iinclude

# Define library paths in addition to standard paths
LIBDIR :=

# Define libraries to link into executable
LIBS :=

# Header files
HEADERS := $(TOPDIR)/include/*.h include/*.h

# Testsuite
OBJDIR := obj
SRC := src/test_simd.cpp src/test_utils.cpp
OBJ := $(TOPDIR)/obj/*.o $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))
DRIVER := src/test_suite.cpp
EXE := testsuite

#######################################

# Targets that are not real files
.PHONY: all clean

all: $(EXE)

$(EXE): $(DRIVER) $(OBJ)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) $< -o $@ $(OBJ) $(LIBS)

$(OBJDIR)/%.o: src/%.cpp $(HEADERS) $(MKFILE)
	@test ! -d $(OBJDIR) && mkdir $(OBJDIR) || true
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) -c $< -o $@ $(LIBS)

clean:
	@test -x $(EXE) && rm $(EXE) || true
	@test -d $(OBJDIR) && rm -r $(OBJDIR) || true

