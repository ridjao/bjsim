CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := bjsim

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
