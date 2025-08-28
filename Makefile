
CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -g

RM = rm -f

TARGET = prog

SRCS = main.cpp

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)


.PHONY: run
run: $(TARGET)
	./$(TARGET) < entrada.txt

.PHONY: clean
clean:
	$(RM) $(TARGET)

.PHONY: debug
debug:
	mkdir -p build/Debug
	$(CXX) $(CXXFLAGS) main.cpp -o build/Debug/outDebug