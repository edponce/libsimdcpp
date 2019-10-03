CXX ?= g++

# Compiler and linker options
CXXFLAGS += -std=c++11

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
SRC := src/cpuid.cpp
OBJ += $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))

DRIVER := src/driver.cpp
EXE := cpuid

DRIVER2 := src/cacheflush.cpp
EXE2 := cacheflush

#######################################

# Targets that are not real files
.PHONY: all clean

all: $(EXE) $(EXE2)

$(EXE): $(DRIVER) $(OBJ) $(HEADERS) $(MAKEFILE_LIST)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) $< -o $@ $(OBJ) $(LIBS)

$(OBJDIR)/%.o: src/%.cpp $(HEADERS) $(MAKEFILE_LIST)
	@test ! -d $(OBJDIR) && mkdir $(OBJDIR) || true
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) -c $< -o $@ $(LIBS)

$(EXE2): $(OBJ) $(HEADERS) $(MAKEFILE_LIST)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) $(DRIVER2) -o $@ $(OBJ) $(LIBS)
	
clean:
	rm -f $(EXE)
	rm -rf $(OBJDIR)
	rm -f $(EXE2)
