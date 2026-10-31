CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -O2

INCLUDES = -Iinclude -Itests

SRC_FILES = $(wildcard src/*.cpp)
TEST_FILES = $(wildcard tests/*.cpp)

TARGET = build/test_runner

LIBS = -lgtest -lgtest_main -pthread

.PHONY: all test clean

all: test

build:
	mkdir -p build

$(TARGET): $(SRC_FILES) $(TEST_FILES) | build
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build