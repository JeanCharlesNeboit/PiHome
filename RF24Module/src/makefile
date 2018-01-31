SRC=main.cpp
#SRC=$(wildcard *.cpp)
EXE=build/main

CXXFLAGS+=-Wall -Wextra -MMD -g -O2
LDFLAGS= /usr/local/lib/librf24.so.1.3.0 /usr/local/lib/librf24network.so.1.0

OBJ=$(addprefix build/,$(SRC:.cpp=.o))
DEP=$(addprefix build/,$(SRC:.cpp=.d))

all: $(OBJ)
	$(CXX) -o $(EXE) $^ $(LDFLAGS)

build/%.o: %.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf build core *.gch

-include $(DEP)
