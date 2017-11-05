## Compiler, tools and options
CXX      = g++
CXXFLAGS =

#DEFINES = -DUSE_MONOTONIC_CLOCK

## Files
OBJECTS = timers_test.o timers.o
TARGET  = timer

## Implicit rules
.SUFFIXES: .cpp

.cpp.o:
	$(CXX) $(DEFINES) -c $(CXXFLAGS) $<

## Build rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET)

