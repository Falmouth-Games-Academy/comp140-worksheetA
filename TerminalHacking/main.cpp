// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"


const int wordLength = 5;
const int numberOfWords = 15;

int temp;
int lives = 4;
std::string guess;

/**
	Compares two strings and returns the number of matching characters in the same position. Case sensetive.

	@param string1, the first string to compare.
	@param string2, the string to compare against. Only compares up to length of string2.
	@returns likness, the number of matching characters. Positions must match as well. Int.
*/
int Compare(std::string secret, std::string guess);

/**
	Converts a string to uppercase.

	@param string, the string to convert.
	@returns string, the now uppercase string.
*/
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

		//If the guess is correct, win and exit loop.
		if (guess == secret)
		{
			std::cout << "\nYou win! \n";
			break;
		}

		//When the guess is incorrect, show likness and reduce lives.
		std::cout << "The likeness is " << Compare(guess, secret) << "\n";
		lives--;

		//Lose and exit loop
		if (lives <= 0)
		{
			std::cout << "\nYou lose! \n";
			break;
		}
				
	}

	//Clear cin buffer and then wait for input to stop program closing instantly.
	std::cin.ignore();
	std::cin.get();
	return 0;
}


//Convert a string to uppercase.
std::string ToUpper(std::string string)
{
	//Iterate over string and convert each character to uppercase.
	for (int i = 0; i < string.length(); i++)
	{
		string[i] = ::toupper(string[i]);
	}

	return string;
}

//Compare two strings and return the number of matching characters in the same position.
int Compare(std::string string1, std::string string2)
{
	int likeness = 0;

	//Iterate over string2 and compare each character with string1.
	for (int i = 0; i < string2.length(); i++)
	{
		if (string2[i] == string1[i])
		{
			likeness++;
		}
	}

	return likeness;
}

