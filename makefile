all: card pile main.cpp
	g++ -pedantic-errors -g main.cpp card pile -o main
card: card.h card.cpp
	g++ -pedantic-errors -c -g card.cpp -o card
pile: pile.h pile.cpp
	g++ -pedantic-errors -c -g pile.cpp -o pile
