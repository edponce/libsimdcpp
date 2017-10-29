## Compiler, tools and options
CC      = gcc
CFLAGS =

#DEFINES = -DUSE_MONOTONIC_CLOCK

## Files
OBJECTS = timers_test.o timers.o
TARGET  = timer

## Implicit rules
.SUFFIXES: .c

.c.o:
	$(CC) $(DEFINES) -c $(CFLAGS) $<

## Build rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET)

