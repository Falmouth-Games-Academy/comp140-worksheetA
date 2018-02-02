// main.cpp: Defines the entry point for the console application.
//
#include <iostream>
#include "stdafx.h"
#include "WordList.h"

const int wordLength = 5;
const int numberOfWords = 15;

int WordMatch(const std::string& guessedWord, const std::string& secret, int wordLength);
void MakeCapitals(std::string & guessedWord, int wordLength);
int GetWordLength(const std::string& guessedWord);


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

	int lifes = 4;
	while (lifes > 0)
	{
		std::string guessedWord;

		// Takes user's written word
		std::cin >> guessedWord;
		std::cout << std::endl;

		// Gets and integer of user's guessed word
		int guessedWordLength = GetWordLength(guessedWord);

		if (guessedWordLength == wordLength)
		{	
			// Transforms all characters into capitals, in case the user has written them in lower
			MakeCapitals(guessedWord, wordLength);

			// Gets the integer of how many character have matched with the secret word
			int matchedCharacters = WordMatch(guessedWord, secret, wordLength);

			// Checks for the winning condition
			if (matchedCharacters == wordLength)
			{
				std::cout << "Winner Winner Chicken Dinner!\n";
			}

			// If the player didn't win, given him a clue of how many character matched his guessed word
			else
			{
				std::cout << "Incorrect. Try one more time! I believe in you!\n";
				std::cout << "The word likeness is " << matchedCharacters << " characters.\n";
				lifes--;
				std::cout << "Lifes left " << lifes << "\n\n";
			}
		}

		// If the user's word does not match the word length, tall him about it!
		else
		{
			std::cout << "Wrong word! At least make it the same length...\n";
		}
	}

	std::cout << "Better luck next time!\n";

	// Pauses the console, to see what happened
	system("pause");

	return 0;
}

int WordMatch(const std::string& guessedWord, const std::string& secret, int wordLength) 
{
	/**
	Gets the integer of matched user's guessed word characters with the secret word
	*/
	int matches = 0;
	for (int i = 0; i < wordLength; i++)
	{
		if (guessedWord[i] == secret[i]) 
		{
			matches++;
		}
	}
	return matches;
}

void MakeCapitals(std::string & guessedWord, int wordLength)
{
	/** 
	Transforms all user's written character into capitals,
	so that it matches all given words
	*/
	for (int i = 0; i < wordLength; i++)
	{
		if (isalpha(guessedWord[i]))
		{
			guessedWord[i] = toupper(guessedWord[i]);
		}
	}
}

int GetWordLength(const std::string& guessedWord)
{
	/**
	Returns an integer of how many characters the user's word has
	*/
	int guessedWordLength = 0;
	for (int i = 0; i < guessedWord.size(); i++)
	{
		guessedWordLength++;
	}
	return guessedWordLength;
}
