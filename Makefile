FLAGS = -pedantic-errors -std=c++11

main: main.o checkwin.o
	g++ $(FLAGS) main.o checkwin.o -o main

checkwin.o: checkwin.cpp checkwin.h
	g++ $(FLAGS) -c checkwin.cpp

main.o: main.cpp checkwin.h
	g++ $(FLAGS) -c main.cpp

clean:
	rm -f checkwin.o main.o main

.PHONY: clean