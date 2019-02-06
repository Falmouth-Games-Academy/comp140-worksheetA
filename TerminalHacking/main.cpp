// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"

const int wordLength = 5;
const int numberOfWords = 15;


int GetLikeness(std::string guessedWord, std::string secretWord)
{
	int likeness = 0;

	for (int i = 0; i < guessedWord.length(); i++)

	{
		if (guessedWord[i] == secretWord[i])
			likeness++;
	}

	return likeness;

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

	bool guessed_word = false;

	std::string guessed;	


	std::cout << "Type in your answer: ";
	std::getline(std::cin, guessed);
	
	int wordLikeness = GetLikeness(guessed, secret);


	if (guessed_word == true)
		std::cout << "Welcome, Dr Shimm.";

	else
		std::cout << "TERMINAL LOCKED.. Seek out an Administrator.";


	return 0;
}
