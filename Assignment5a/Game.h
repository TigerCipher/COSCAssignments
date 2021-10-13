#pragma once


class Game
{
	enum AnswerState
	{
		LOW = -1,
		CORRECT,
		HIGH
	};

public:
	explicit Game(const int limit = 50): mLimit(limit) {}


	void play();


private:
	/// <summary>
	/// Checks if the player's guess is correct
	/// </summary>
	/// <param name="choice">The player's guess</param>
	/// <returns>LOW(-1) if too low, HIGH(1) if too high, and CORRECT(0) if correct</returns>
	AnswerState isPlayerCorrect(int choice) const;

	void randomizeCompChoice();


	int mLimit;
	int mCompChoice {};
	bool mPlaying = true;
};
