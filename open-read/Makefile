#
# We are using implicit rules here
#
CC = gcc
CFLAGS = -g -Wall -std=c17 -fsanitize=address
TARGETS = open-read

.PHONY: all clean

all: $(TARGETS)

run: $(TARGETS)
	./$(TARGETS)

run1: $(TARGETS)
	./$(TARGETS) 1

run2: $(TARGETS)
	./$(TARGETS) 2

run3: $(TARGETS)
	./$(TARGETS) 3

clean:
	rm -f *.o $(TARGETS)

