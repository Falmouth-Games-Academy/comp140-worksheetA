// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"

const int wordLength = 5;
const int numberOfWords = 15;
const int startingLives = 4;

int main()
{
	// Seed the random number generator with the current time,
	// to ensure different results each time the program is run
	srand(static_cast<unsigned int>(time(nullptr)));

	// Initialise word list
	WordList words(wordLength);

	// Create a set to hold the list of options
	std::set<std::string> options;

	// Fill the set with more words
	// Using a set for options guarantees that the elements are all different
	while (options.size() < numberOfWords)
	{
		std::string word = words.getRandomWord();
		options.insert(word);
	}
	
	// Choose secret word
	std::string secret = words.getSecretWord(options, 2, 6, 10);

	// Display all words
	for each (std::string word in options)
	{
		std::cout << word << std::endl;
	}
	
	// Main loop
	int lives = startingLives;
	std::string guess = "";
	while (true)
	{
		// Ask the user for their guess
		std::cout << "Enter your guess" << std::endl;

		// Save their guess
		std::cin >> guess;

		// Is the guess in our list of words
		if (!words.containsWord(guess))
		{
			std::cout << "Invalid guess" << std::endl;
			continue;
		}

		// Is the guess correct
		if (guess == secret)
		{
			std::cout << "You win!";
			break;
		}

		// Calculate likeness between secret word and guess
		int score = words.getLikness(secret, guess);

		// Display the likeness score to the player
		std::cout << "Likeness score: " << score << std::endl;

		// Remove one life
		lives--;

		// End the game if we don't have enough lives to continue
		if (lives <= 0) 
		{
			std::cout << "You lose!";
			break;
		}

	}

	return 0;
}
