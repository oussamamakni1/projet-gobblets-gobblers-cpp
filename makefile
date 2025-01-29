TARGET = game
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
SRCS = main.cpp board.cpp cell.cpp piece.cpp
OBJS = $(SRCS:.cpp=.o)
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGET)
run: $(TARGET)
	./$(TARGET)
.PHONY: all clean run