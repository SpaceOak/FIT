.PHONY: all compile run doc clean
.DEFAULT_GOAL = compile

CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic-errors
LDFLAGS = -lncurses
EXECUTABLE = dubinden
SOURCES := $(wildcard src/*.cpp)
-include $(SOURCES:.cpp=.d)

%.o: %.cpp
	@echo "$^ \t->\t $@"
	@$(CXX) $(CXXFLAGS) -c -o $@ -c $< $(LDFLAGS)
	@$(CXX) $(CXXFLAGS) -MM -MT $*.o $*.cpp $(LDFLAGS) > $*.s

all: compile

compile: $(SOURCES:.cpp=.o)
	@$(CXX) $(CXXFLAGS) $(SOURCES:.cpp=.o) -o $(EXECUTABLE) $(LDFLAGS)
	@echo "Compiled"

run: compile
	@./$(EXECUTABLE)
	@echo "It works!!!"

doc:
	doxygen Doxyfile
	@echo "You wount read this"

clean:
	@rm -f $(EXECUTABLE)
	@rm -f -- src/*.o
	@rm -f -- src/*.s
	@rm -rf -- doc/
	@echo "Clean enough."
