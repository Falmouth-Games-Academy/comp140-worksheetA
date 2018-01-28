// main.cpp: Defines the entry point for the console application.
//
#include <iostream>
#include "stdafx.h"
#include "WordList.h"

const int wordLength = 5;
const int numberOfWords = 15;

int WordMatch(std::string guessedWord, std::string secret, int wordLength);


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

	int lives = 4;
	while (lives != 0)
	{
		std::string guessedWord;
		std::cin >> guessedWord;
		int matchedCharacters = WordMatch(const std::string guessedWord, const std::string secret, int wordLength);
		if (matchedCharacters == wordLength)
		{
			std::cout << "Winner Winner Chicken Dinner!";
		}
		else
		{
			std::cout << "The word likeness is " << matchedCharacters << " characters." << std::endl;
			std::cout << "Try one more time! I believe in you!" << std:endl;
			lives--;
		}
	}
	std::cout << "Better luck next time!" << std::endl;


	return 0;
}

int WordMatch(const std::string guessedWord, const std::string secret, int wordLength)  // ??
{
	int matches = 0;
	for (int i = 0, i < wordLength, i++)
	{
		if (guessedWord[i] == secret[i])  // ??
		{
			matches++;
		}
	}
	return matches;
}