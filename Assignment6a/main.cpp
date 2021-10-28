// Matthew Rogers
// 10/27/2021
// Assignment 6a - Temperature Table


// If there is another temperature related assignment in the future,
// I will make a gui calculator for it. I was going to for this, but
// blame my chemistry test for getting in the way

#include <iostream>
#include <iomanip>

// Had to at least do something. Especially since celsiusConverter
//sounds like a class name rather than function name :P
class TemperatureCalculator
{
public:
	static float convertToCelsius(float f);
	static float convertToFahrenheit(float c);
};

float TemperatureCalculator::convertToCelsius(const float f)
{
	return 5.0f / 9.0f * (f - 32.0f);
}

float TemperatureCalculator::convertToFahrenheit(const float c)
{
	return c * (9.0f / 5.0f) + 32.0f;
}


// global constants
constexpr int CELSIUS_FAHRENHEIT = 0;
constexpr int FAHRENHEIT_CELSIUS = 1;

// global function prototype
void print_table(int type);

int main(int argc, char** argv)
{
	print_table(FAHRENHEIT_CELSIUS);
	std::cout << "\n\n";
	print_table(CELSIUS_FAHRENHEIT);

	return 0;
}


void print_table(const int type)
{
	std::string title = "Invalid table";
	int width = 10;
	if (type == FAHRENHEIT_CELSIUS)
	{
		title = "Fahrenheit   Celsius\n";
		width = 23;
	}
	else if (type == CELSIUS_FAHRENHEIT)
	{
		title = "Celsius   Fahrenheit\n";
		width = 26;
	}

	std::cout << std::right << std::setw(width) << title;
	std::cout << "------------------------\n";

	for (int i = 0; i <= 100; i += 10)
	{
		float conversion = 0.0f;
		if (type == FAHRENHEIT_CELSIUS)
			conversion = TemperatureCalculator::convertToCelsius(static_cast<float>(i));
		else
			if (type == CELSIUS_FAHRENHEIT)
				conversion = TemperatureCalculator::convertToFahrenheit(static_cast<float>(i));
		std::cout << std::right << std::setw(12) << i << "\t"
				<< std::fixed << std::setprecision(1)
				<< std::right << std::setw(6)
				<< conversion << std::endl;
	}
}
