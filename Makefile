CXX=clang++
CXXFLAGS=-O3 -Wall -Werror -pedantic -std=c++14

test_functors: test_functors.cc

clean:
	rm -f test_functors
