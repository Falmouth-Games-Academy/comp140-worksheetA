// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"
#include <string>


const int wordLength = 5;
const int numberOfWords = 15;

bool correctWord(std::string generatedWord, std::string playerWord)
{
	if (generatedWord == playerWord)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	std::string playerWord;
	int lives = 5;
	bool win = false;
	bool reset = false;
	std::string previousGuess;
	// Seed the random number generator with the current time,
	// to ensure different results each time the program is run
	srand(static_cast<unsigned int>(time(nullptr)));

	// Initialise word list
	WordList words(wordLength);
	// Run the game while the has lives or has not won
	lives = 5;
	previousGuess = "";
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
	do
	{
		// Get the input from player while the word is the same length and is also in the set.
		do
		{
			do
			{
				std::cout << "Guess the word! ";
				std::cin >> playerWord;
			} while (playerWord == previousGuess);
			previousGuess = playerWord;
		} while ((playerWord.size() - secret.size() != 0) || (options.find(playerWord) != options.end()));
		if (correctWord(secret, playerWord))
		{
			// Exit if player has won.
			std::cout << "Correct! The word was " << secret << std::endl;
			win = true;
		}
		else
		{
			// Decrement if the player got it wrong
			int likeness = WordList::getLikeness(secret, playerWord);
			lives--;
			std::cout << "Your likeness is " << likeness << " Your lives are " << lives << std::endl;
		}
	} while ((lives > 0) && (!win));
	// Print loss statement if the player lost
	if (lives == 0)
	{
		std::cout << "You lost!" << std::endl;
	}
	// Check if the player wishes to play again
	do
	{
		std::cout << "Would you like to play again? y/n " << std::endl;
		std::cin >> playerWord;
		if (tolower(playerWord.at(0) == 'y'))
		{
			main();
		}
		else if (tolower(playerWord.at(0)) == 'n')
		{
			return 0;
		}
	} while ((tolower(playerWord.at(0)) != 'y') || (tolower(playerWord.at(0)) != 'n'));
	return 0;
}
