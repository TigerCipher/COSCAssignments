// Assignment 1 - Twitter
// Matthew Rogers
// 09/12/2021

// Couldn't really think of a way to make this one too much more fun
// other than the one idea I had about http requests, but I didn't hear
// back from my email about using a header only http api
// So I simply decided to add a bit of OOP and user input so it's at
// least a little bit spicy


#include <iostream>

class Twitter
{
public:
	explicit Twitter(const int followers) : mFollowers(followers) {}

	int getNewFollowers(const float growth) const
	{
		return static_cast<int>(mFollowers * (growth / 100.0f));
	}

	int getNumFollowers() const
	{
		return mFollowers;
	}

	void setFollowers(const int followers)
	{
		mFollowers = followers;
	}
	
private:
	int mFollowers;
};


int main(int argc, char** argv)
{

	int startingFollowers = 12000;

	std::cout << "How many followers should this twitter user start with? ";
	std::cin >> startingFollowers;

	

	float growth = -1.0f;
	std::cout << "How much did this user grow by? [0 - 100 %] ";
	bool validPercentage = false;
	while(!validPercentage)
	{
		std::cin >> growth;
		if(growth >= 0.0f && growth <= 100.0f)
		{
			validPercentage = true;
		}
		else
		{
			std::cout << "\nPlease enter a valid percentage value: ";
		}
	}

	Twitter user(startingFollowers);
	const int newFollowers = user.getNewFollowers(growth);
	user.setFollowers(startingFollowers + newFollowers);
	const int totalFollowers = user.getNumFollowers();

	std::cout << "\nMarcelo started the week with " << startingFollowers << " followers.\n";
	std::cout << "He gained " << newFollowers << " followers this week.\n";
	std::cout << "He ended the week with " << totalFollowers << " total followers.";
	
	
	return 0;
}