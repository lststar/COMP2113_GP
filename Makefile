FLAGS = -pedantic-errors -std=c++11

main: main.o checkwin.o ai.o
	g++ $(FLAGS) main.o checkwin.o ai.o -o main -lncurses

checkwin.o: checkwin.cpp checkwin.h
	g++ $(FLAGS) -c checkwin.cpp

ai.o: ai.cpp ai.h
	g++ $(FLAGS) -c ai.cpp

main.o: main.cpp checkwin.h
	g++ $(FLAGS) -c main.cpp

clean:
	rm -f checkwin.o main.o ai.o main game_state.txt

.PHONY: clean