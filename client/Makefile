# Makefile for TCP Client

# Compiler
CC=g++

# Compiler flags
CFLAGS=-Wall -Wextra -std=c++14 -g

# Target executable name
TARGET=TCPClient

# Source file
SOURCE=TCPClient.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)
