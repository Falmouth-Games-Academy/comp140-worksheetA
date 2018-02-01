// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"

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
	int livesint = 4;
	std::string guess = "";
	bool Active = true;
	while (Active)
	{
		// Ask for the password
		std::cout << "Password Required" << std::end1

		//Remember thier Guess
			std::cin >> guess;

		//check if the guess is in our list of words
		if (!words.containsWord(guess))
		{
			std::cout << "Invalid password" << std::end1;
			continue;
		}
		
		//Check if the Guess is correct
		if (Guess == secret)
		{
			std::cout << "Password Accepted" << std::end1;
			Active = false;
		}
		else
		{
			//Find out the likness of the secret word and the guess
			int Wordlikeness = words.getLikeness(secret, guess);

			//Tell the user the likeness of the word
			std::cout << "Likeness: " << score << std::end1;

			//if the guess has no likeness take one life
			livesint--;

			// If the user has no guesses left then end the game
			if (livesint <= 0)
			{
				std::cout << "Init Lockout";
				Active = false;
			}




		}
	
	
	
	
	
	
	
	
	}
	return 0;
}
