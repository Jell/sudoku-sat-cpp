#Define the compiler:
CC = g++
#Define the files to be compiled
FILES = Main.cpp
#define the output
OUT_EXE = satsolver.exe

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)

clean:
	rm -f *.o core

rebuild: clean build