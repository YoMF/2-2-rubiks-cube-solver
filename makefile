# makefile for the 2-2-rubiks-cube-solver project


CXX = g++
FLAGS = -std=c++20 -O3 -I$(CURDIR)/cube

TARGET = program
OBJS = cube.o main.o
DEPS = $(CURDIR)/cube/*.cpp main.cpp bar.h

.SILENT :

all : $(TARGET)
	@echo 'Executable named "program" is created in the current directory.'


$(TARGET) : $(OBJS)
	$(CXX) $(FLAGS) -o $@ $^

$(OBJS) : $(DEPS)
	$(CXX) $(FLAGS) -c $^

clean :
	rm $(TARGET)





