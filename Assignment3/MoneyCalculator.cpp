#include "MoneyCalculator.h"


const int MoneyCalculator::NICKEL_CONV = 5;
const int MoneyCalculator::DIME_CONV = 10;
const int MoneyCalculator::QUARTER_CONV = 25;

int MoneyCalculator::getNickels() const
{
	return mCents / NICKEL_CONV;
}

int MoneyCalculator::getDimes() const
{
	return mCents / DIME_CONV;
}


int MoneyCalculator::getQuarters() const
{
	return mCents / QUARTER_CONV;
}

