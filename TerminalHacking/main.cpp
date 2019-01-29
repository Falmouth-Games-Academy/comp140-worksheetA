// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"

const int wordLength = 5;
const int numberOfWords = 15;

const int numberOfGuesses = 4;

int GetLinkness(std::string guessedWord, std::string secretWorld)
{
	int likeness = 0;

	//use the length of guessedWord if its shorter than secretWord so we dont errors if it is longer
	int loopCount = static_cast<unsigned int>(guessedWord.length() < secretWorld.length() ? guessedWord.length() : secretWorld.length());

	for(int i = 0; i < loopCount; i++)
	{
		// count if the letters in the same position match.
		if (guessedWord[i] == secretWorld[i])
			likeness++;
	}

	return likeness;

}

bool IsVaildOption(std::string guessedWord, std::set<std::string>* wordOptions)
{
	return wordOptions->count(guessedWord) > 0;
}

std::string GetRandomWordOfLikeness(int likeness, WordList* words, std::string secretWorld)
{

	std::string word = "";

	do {
		word = words->getRandomWord();
		
	} while (word.length() > 0 && GetLinkness(word, secretWorld) != likeness);

	return word;
}

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

	// set the amount of remaining guesses
	int remainingGuesses = numberOfGuesses;

	// Fill the set with more words
	// Using a set for options guarantees that the elements are all different
	while (options.size() < numberOfWords)
	{
		// get a rand number between 0 and wordLength-1
		int likeness = (rand() % (wordLength-1));	
		std::string word = GetRandomWordOfLikeness(likeness, &words, secret);

		options.insert( word );
	}
	
	// Display all words
	for each (std::string word in options)
	{
		std::cout << word << std::endl;
	}

	// TODO: implement the rest of the game
	while(remainingGuesses > 0) 
	{
		std::string guessedWord;	// set string var here so it is reset on each atempt.

		//Get the user to enter there guess
		std::cout << "Enter your guess: ";
		std::cin >> guessedWord;

		// if users input is invaild print message and continue
		if (!IsVaildOption(guessedWord, &options))
		{
			std::cout << "Invalid Guess" << std::endl;
			continue;
		}
		
		// Check if the input is correct
		if (guessedWord == secret)
		{
			std::cout << "You Win!" << std::endl;
			break;
		}

		// get the likeness and print the value
		int likeness = GetLinkness(guessedWord, secret);
		std::cout << "Likeness " << likeness << " of " << secret.length() << std::endl;

		// Decrement lives and check we still have remaining goes.
		remainingGuesses--;

		if (remainingGuesses == 0)
			break;

		std::cout << "You have " << remainingGuesses << " remaining guesses" << std::endl;


	}
	
	std::cout << "You lose";


	return 0;
}

