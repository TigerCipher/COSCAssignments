// Class is simple. I just wanted to clean up the main source file a bit

#pragma once

// conversion constants
// I generally avoid macros when I can, and for something like this a simple const
// is less efficient than constexpr (which I realize only matters in large projects, like games)
constexpr int NICKEL_CONV = 5;
constexpr int DIME_CONV = 10;
constexpr int QUARTER_CONV = 25;

class MoneyCalculator
{
public:
	// I see a lot of people who leave "explicit" out. I like using it to avoid situations where an overloaded function
	// would be confused and unsure whether to use the one with MoneyCalculator as a parameter or the one with int
	explicit MoneyCalculator(const int cents) : mCents(cents) {}

	int getNickels() const;
	int getDimes() const;
	int getQuarters() const;


private:
	int mCents;

};

