#SRC=src/main.cpp
SRC=$(wildcard src/*.cpp)
EXE=bin/main

CXXFLAGS= -Wall -Wextra -MMD -g -O2 -std=c++11
INCLUDES= -Iinclude
LDFLAGS= -Llib -lrf24 -pthread -lboost_system -lcrypto -lssl

#OBJ=$(addprefix build/,$(SRC:.cpp=.o))
#DEP=$(addprefix build/,$(SRC:.cpp=.d))
OBJ=$(subst src/,build/,$(SRC:.cpp=.o))
DEP=$(subst src/,build/,$(SRC:.cpp=.d))

all: $(OBJ)
	@mkdir -p bin
	$(CXX) -o $(EXE) $^ $(LDFLAGS)

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDES)

clean:
	@rm -rf build bin core *.gch
	@echo "Cleanup completed!"

-include $(DEP)
