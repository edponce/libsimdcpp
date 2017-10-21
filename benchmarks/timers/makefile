## Compiler, tools and options
CC      = gcc
CCFLAGS =

## Files
OBJECTS = c_timer_test.o c_timer.o
TARGET  = timer

## Implicit rules
.SUFFIXES: .c

.c.o:
	$(CC) -c $(CCFLAGS) $<

## Build rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET)

