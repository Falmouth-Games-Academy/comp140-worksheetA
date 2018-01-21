// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"
#include <stdlib.h>

const int wordLength = 5;
const int numberOfWords = 15;

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

	// TODO: implement the rest of the game
	bool running = true;
	int tries = 5;

	std::string userInput;
	std::string secretWord;

	while (running)
	{
		std::cin >> userInput;
		if (userInput != secret && tries > 0)
		{
			tries = tries - 1;
			int correctLetters = 0;

			for (const char Uchar : userInput)
			{
				for (const char Schar : secret)
				{
					if (Uchar == Schar)
					{
						correctLetters++;
					}
				}
			}

			std::cout << "WORNG!!! " << correctLetters << "/5";
		}
		else if (userInput == secret)
		{
			std::cout << "CORRECT PASSWORD - ACCESS GRANTED";
		}

		else
		{
			std::cout << "-ERROR- NO MORE ATTEMPTS ALLOWED - SHUTTING DOWN";
			_sleep(1500);
			return 0;
		}
	}


	return 0;
}
