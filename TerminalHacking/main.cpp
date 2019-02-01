// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"

const int wordLength = 5;
const int numberOfWords = 15;
int livesRemaining = 4;

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
	while (livesRemaining > 0) {
		std::string guess;
		int letterCount = 0;
		std::cin >> guess;
		std::cout << "your guess was: " + guess << std::endl;
		if (guess == secret)
		{
			std::cout << "You win!" << std::endl;
			break;
		}
		else {

			for (int i = 0; i < secret.length(); i++)
			{
				if (guess[i] == secret[i])
				{
					letterCount++;
				}


			}


			std::cout << "You got " << letterCount << " letters correct";
			std::cout << "You lost a life, try again!" << std::endl;
			std::cin >> guess;
			std::cout << "your guess was: " << guess << std::endl;
			livesRemaining--;


			if (livesRemaining == 0)
			{
				std::cout << "You're out of lives therefore you lose!" << std::endl;
			}

		}
	}





	return 0;
}
