// Matthew Rogers
// 10/17/21
// Assignment 5b - Multiplication Table

#include <iomanip>
#include <iostream>

int main(int argc, char** argv)
{
	int rows, cols;

	std::cout << "Multiplcation Table Tool\n\n";
	std::cout << "How many rows would you like? ";
	std::cin >> rows;
	std::cout << "\nHow many columns would you like? ";
	std::cin >> cols;

	std::cout << std::setw(4) << " ";
	for(int i = 0; i < cols; i++)
	{
		std::cout  << std::setw(6) << i + 1;// << "\t";
	}
	std::cout << "\n";
	for(int i = 0; i < cols * 7; i++)
	{
		std::cout << "-";
	}
	std::cout << "\n";

	for(int r = 1; r <= rows; r++)
	{
		std::cout << std::setw(3) << r << "|";
		for(int c = 1; c <= cols; c++)
		{
			std::cout << std::setw(6) << r * c;
		}
		std::cout << "\n";
	}

	return 0;
}