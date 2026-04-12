# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Target executable name
TARGET = taskmanager

# Source files
SRCS = main.c task.c file.c

# Object files (auto-generated from SRCS)
OBJS = $(SRCS:.c=.o)

# Default target - builds the program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile main.c
main.o: main.c task.h file.h
	$(CC) $(CFLAGS) -c main.c

# Compile task.c
task.o: task.c task.h
	$(CC) $(CFLAGS) -c task.c

# Compile file.c
file.o: file.c file.h task.h
	$(CC) $(CFLAGS) -c file.c

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Compile and run test program
test: test_runner.c task.c file.c
	$(CC) $(CFLAGS) -o test_runner test_runner.c task.c file.c
	./test_runner

# Declare targets that aren't files
.PHONY: clean run test