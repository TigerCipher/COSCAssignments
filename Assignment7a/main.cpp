// Matthew Rogers COSC 1436.900
// 11/07/2021
// Assignment 7a - Diving Judging Program

#include <algorithm>
#include <iostream>

void move_max_min_to_end(double* arr, int size);

int main(int argc, char** argv)
{

	double scores[5];

	std::cout << "Please enter the 5 judging scores:\n";

	for(int i = 0; i < 5; i++)
	{
		std::cout << "Dive " << i + 1 << ": ";
		double a = -1;
		do
		{
			std::cin >> a;
			if(a < 0 || a > 10)
			{
				std::cout << "Score must be between 0 and 10\n";
			}
		}while(a < 0 || a > 10);
		scores[i] = a;
		std::cout << std::endl;
	}


	std::cout << "\nThe results are in, here are the 5 scores: ";
	for(double score : scores)
	{
		std::cout << score << " ";
	}

	move_max_min_to_end(scores, 5);
	std::cout << "\nThe highest score of " << scores[4] << " and lowest score of " << scores[3] << " were dropped\n";

	double total = 0;
	for(int i = 0; i < 3; i++)
	{
		total += scores[i];
	}

	std::cout << "The raw score for this dive is: " << total;
	
	return 0;
}

// Uses algorithm functions to find max and min and swap them to the last 2 indices
// A lot cleaner than going through a loop in my opinion - why recreate the wheel
void move_max_min_to_end(double* arr, const int size)
{
	double* last = arr + size - 1;
	double* max = std::max_element(arr, arr + size);
	std::iter_swap(max, last);
	double* min = std::min_element(arr, arr + size - 1);
	std::iter_swap(min, last - 1);
}