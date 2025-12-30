# compiler to be used
CC = gcc

# compiler flags
CFLAGS = -Wall -g

# target executable
TARGET = comp

$(TARGET): main.c scan.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c scan.c

run1: $(TARGET) in01
	./$(TARGET) in01

run2: $(TARGET) in02
	./$(TARGET) in02

run3: $(TARGET) in03
	./$(TARGET) in03

clean: 
	rm -rf *.o $(TARGET)
	