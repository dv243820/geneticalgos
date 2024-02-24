CXX = g++
CXXFLAGS = -Wall

# Source files
SRC = geneticalgorithm.cpp
HDR = genetic.h

# Output executable
TARGET = geneticalgorithm

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
