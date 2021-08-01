CXX = clang++
CXXFLAGS = -Wall -Wextra -pedantic -g -std=c++17
LINK.o = $(LINK.cc)
TEST_OBJS = test_main.o test_list.o linked_list.o

all: test_main

test_main: $(TEST_OBJS)

clean:
	rm -f *.o test_main