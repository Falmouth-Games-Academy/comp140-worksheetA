// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"


const int wordLength = 5;
const int numberOfWords = 15;

int temp;
int lives = 4;
std::string guess;

int Compare(std::string secret, std::string guess);
std::string ToUpper(std::string string);

int main()
{
	// Seed the random number generator with the current time,
	// to ensure different results each time the program is run
	srand(static_cast<unsigned int>(time(nullptr)));

	// Initialise word list
	WordList words(wordLength);

	// Choose secret word
	std::string secret = words.getRandomWord();

	// Create a set to hold the list of options
	std::set<std::string> options;

	// Put the secret word in the set
	options.insert(secret);

	// Fill the set with more words
	// Using a set for options guarantees that the elements are all different
	while (options.size() < numberOfWords)
	{
		std::string word = words.getRandomWord();
		options.insert(word);
	}

	// Display all words
	for each (std::string word in options)
	{
		std::cout << word << std::endl;
	}


	//Main game loop

	while (true)
	{
		std::cout << "\nYou have: " << lives << " lives. Please enter a guess. \n";
		std::cin >> guess;
		guess = ToUpper(guess);

		//If guess is not in list of possible words input again.
		if (options.count(guess) == 0)
		{
			std::cout << "Invalid guess \n";
			continue;
		}

		//If the guess is correct exit loop.
		if (guess == secret)
		{
			std::cout << "\nYou win! \n";
			break;
		}

		std::cout << "The likeness is " << Compare(secret, guess) << "\n";
		lives--;

		if (lives <= 0)
		{
			std::cout << "\nYou lose! \n";
			break;
		}
				
	}

	std::cin.ignore();
	std::cin.get();
	return 0;
}

std::string ToUpper(std::string string)
{
	for (int i = 0; i < string.length(); i++)
	{
		string[i] = ::toupper(string[i]);
	}

	return string;
}

int Compare(std::string secret, std::string guess)
{
	int likeness = 0;

	for (int i = 0; i < secret.length(); i++)
	{
		if (secret[i] == guess[i])
		{
			likeness++;
		}
	}

	return likeness;
}

