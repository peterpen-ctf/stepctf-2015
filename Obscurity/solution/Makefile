.PHONY: all run
all: run
run: main.py solver
	./main.py
solver: solver.cc cipher.h
	g++ -O2 solver.cc -o $@