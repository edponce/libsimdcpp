# Eduardo Ponce
# 11/2017
# Makefile for libsimdcpp-examples

# Compiler and linker options
CXXFLAGS +=

# Linker options
LFLAGS +=

# Preprocessor definitions
DEFINES +=

# Define header paths in addition to standard paths
INCDIR +=

# Define library paths in addition to standard paths
LIBDIR +=

# Define libraries to link into executable
LIBS +=

# Header files
HEADERS +=

# Example
OBJDIR := obj
SRC :=
OBJ += $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))

DRIVER := example.cpp
EXE := example

#######################################

# Targets that are not real files
.PHONY: all clean

all: $(EXE)

$(EXE): $(DRIVER) $(OBJ) $(HEADERS) $(MAKEFILE_LIST)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) $< -o $@ $(OBJ) $(LIBS)

$(OBJDIR)/%.o: src/%.cpp $(HEADERS) $(MAKEFILE_LIST)
	@test ! -d $(OBJDIR) && mkdir $(OBJDIR) || true
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) -c $< -o $@ $(LIBS)

clean:
	rm -f $(EXE)
	rm -rf $(OBJDIR)

