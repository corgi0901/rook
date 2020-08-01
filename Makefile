CXXFLAGS=-std=c++17 -g
SRCS=*.cpp *.hpp
CXX=g++

rook: $(SRCS)
	$(CXX) -o rook $(SRCS) $(CXXFLAGS)

test: rook
	./test.sh

clean:
	rm -f rook *~

.PHONY: test clean