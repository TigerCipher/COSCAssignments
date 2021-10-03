#include "MoneyCalculator.h"



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

