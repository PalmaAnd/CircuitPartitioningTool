# Compiler
CC = gcc

# Flags used by the compiler
# -O3: 					Optimization level 3
# -MMD: 				Generate dependency files (.d) from source files (.c) -> Benotungskriterien Nr. 9
# -MP: 					Adds phony targets for each dependency file to avoid errors if the header is deleted
# -Wall: 				Enable all warnings
# -fsanitize=address: 	memory error detector
CFLAGS = -Wall -fsanitize=address -O3 -MMD -MP

PROGRAMS = programm

OBJECTS = gate.o connection.o queue.o

ALLOBJECTS = $(OBJECTS) $(patsubst %,%.o,$(PROGRAMS))

# Default target: Will build everything defined by PROGRAMS when only make is entered
default: $(PROGRAMS)

programm: $(OBJECTS)

# Clean rule: Remove compiled object files, dependency files, and the program executables
clean:
		-rm -f $(ALLOBJECTS) $(ALLOBJECTS:%.o=%.d) $(PROGRAMS)

-include $(ALLOBJECTS:%.o=%.d)
