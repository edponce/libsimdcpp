# Eduardo Ponce
# 10/2017
# Makefile for libsimdcpp

# Get name of makefile
MKFILE := $(MAKEFILE_LIST)

# Define header paths in addition to standard paths
INCDIR := -I../include

# Define library paths in addition to standard paths
LIBDIR :=

# Define libraries to link into executable
LIBS :=

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

