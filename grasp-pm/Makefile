CC=g++ -std=c++11

all: clean directory binario clear

run: clean directory binario clear execute

binario: Parser.o Grasp.o main.o
	$(CC) -o build/grasp-pm Parser.o Grasp.o main.o

Parser.o: Parser.cpp Parser.h
	$(CC) -c Parser.cpp
	
Grasp.o: Grasp.cpp Grasp.h
	$(CC) -c Grasp.cpp

main.o: main.cpp
	$(CC) -c main.cpp

clear: 
	rm -rf *.o

clean:
	rm -rf *.o
	rm -rf build/grasp-pm
	rm -rf build

execute: 
	./build/grasp-pm

directory:
	mkdir build
