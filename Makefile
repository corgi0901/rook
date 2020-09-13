## Directory defines
BUILDDIR = ./build

## Target name
TARGET = rook

## Compiler options
CXX = g++
CXXFLAGS = -O2 -Wall

SRCS := $(wildcard *.cpp)
SRCS += $(wildcard */*.cpp)
OBJS := $(SRCS:%.cpp=$(BUILDDIR)/%.o)
DEPS := $(OBJS:.o=.d)

CPPFLAGS := -MMD -MP

# Target
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

# c++ source
$(BUILDDIR)/%.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean rebuild test

clean:
	$(RM) -r $(BUILDDIR) $(TARGET)

rebuild:
	make clean && make

test:
	make all
	./test.sh

-include $(DEPS)

MKDIR_P = mkdir -p
