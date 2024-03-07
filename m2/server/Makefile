C = g++
CFLAGS = -Wall -std=c++11
TARGET = TCPServer
SRC = main.cpp TCPServer.cpp ServerDecorator.cpp Logger.cpp

# Default target
all: $(TARGET)

# Link the object file to create the executable
$(TARGET): $(SRC)
	$(C) $(CFLAGS) $(SRC) -o $(TARGET)

# Clean up
clean:
	$(RM) $(TARGET)
