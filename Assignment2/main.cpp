// Matthew Rogers
// 09/19/2021
// Assignment 2: Crypto currency Converter

// Sadly this week and today has been very busy, no time to make
// things more exciting ;-;

#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
	const float bitPerDollar = 0.000021f;
	const float ethPerDollar = 0.00028f;

	float dollars;
	std::cout << "Please enter a dollar ammount to convert into Bitcoin and Ethereum:\n";
	std::cin >> dollars;

	std::cout << "\nUsing the conversion rates of "
			<< std::setprecision(1) << std::scientific << bitPerDollar
			<< " Bitcoin per dollar and "
			<< std::setprecision(5) << std::fixed << ethPerDollar
			<< " Ethereum per dollar:\n\n";

	std::cout << std::setprecision(0) << dollars << " dollars = "
			<< std::setprecision(3) << bitPerDollar * dollars
			<< " Bitcoin.\n";
	
	std::cout << std::setprecision(0) << dollars << " dollars = "
			<< std::setprecision(3) << ethPerDollar * dollars
			<< " Ethereum.\n";

	return 0;
}
