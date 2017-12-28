SRC=main.cpp
#SRC=$(wildcard *.cpp)
EXE=build/main

CXXFLAGS+=-Wall -Wextra -MMD -g -O2
LDFLAGS= /usr/local/lib/librf24.so.1.3.0
RFOBJ=#RF24.o spi.o bcm2835.o

OBJ=$(addprefix build/,$(SRC:.cpp=.o)) $(addprefix ../lib/RF24/,$(RFOBJ))
DEP=$(addprefix build/,$(SRC:.cpp=.d))

all: $(OBJ)
	$(CXX) -o $(EXE) $^ $(LDFLAGS)

build/%.o: %.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf build core *.gch

-include $(DEP)
