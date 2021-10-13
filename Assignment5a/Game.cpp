#include "Game.h"
#include <cstdlib>
#include <iostream>
#include <ctime>


Game::AnswerState Game::isPlayerCorrect(const int choice) const
{
	if (mCompChoice > choice)
		return LOW;
	if (mCompChoice < choice)
		return HIGH;
	return CORRECT;
}

void Game::play()
{
	int lowestScore = 100000;
	while (mPlaying)
	{
		randomizeCompChoice();
		std::cout << "I'm thinking of a number, what is it? ";
		AnswerState state = LOW;
		int guesses       = 0;
		while (state != CORRECT)
		{
			int guess;
			std::cin >> guess;
			state = isPlayerCorrect(guess);
			if (state == LOW)
			{
				std::cout << "Too low, try again: ";
			}
			else if (state == HIGH)
			{
				std::cout << "Too high, try again: ";
			}
			guesses++;
		}

		std::cout << "\nCongratulations! You guessed it in " << guesses << " tries!\n";

		if(guesses < lowestScore)
		{
			lowestScore = guesses;
			std::cout << "*** Congratulations! You've set a new record for the lowest number of guesses! ***\n";
		}
		
		std::cout << "Want to play again? [y/n] ";
		char playAgain;
		std::cin >> playAgain;

		mPlaying = playAgain == 'y' || playAgain == 'Y';
	}
}

void Game::randomizeCompChoice()
{
	srand(time(nullptr));
	mCompChoice = rand() % mLimit + 1;
}
