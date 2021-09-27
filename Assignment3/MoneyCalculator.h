#pragma once


class MoneyCalculator
{
public:
	explicit MoneyCalculator(const int cents) : mCents(cents) {}

	int getNickels() const;
	int getDimes() const;
	int getQuarters() const;


private:
	int mCents;

	const static int NICKEL_CONV;
	const static int DIME_CONV;
	const static int QUARTER_CONV;
};

