# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11

# Target executable
TARGET = s

# Source files and object files
SRCS = main.cpp Student.cpp StudentManager.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target to build the program
all: $(TARGET)

# Rule to link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile each .cpp file into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(OBJS) $(TARGET)
