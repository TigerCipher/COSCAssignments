// Matthew Rogers
// 10/12/21
// Assignment 5a - Guessing Game

#include <iostream>
#include "Game.h"

int main(int argc, char** argv)
{
	std::cout << "Welcome to the guessing game! I'll think of a number between 1"
			" and a number of your choice, and you guess what it is.\n";
	std::cout << "What should the upper limit be? ";
	int limit;
	std::cin >> limit;
	
	Game game(limit);
	game.play();
	return 0;
}
