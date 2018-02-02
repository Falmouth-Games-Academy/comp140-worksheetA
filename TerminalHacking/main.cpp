// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"
#include <windows.h>
#include <ctype.h>
#include "functions.h"
#include "main.h"


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


	std::string userInput;

	bool running = true;
	int attempts = 3;
	int notInList = 0;

	while (running)
	{
		std::cin >> userInput;

		//converts users input to uppercase
		userInput = MakeUppercase(userInput);
	
		//checks if user has chosen a word from the list
		for each (std::string word in options)
		{
			if ((userInput != word) && (userInput != secret))
			{
				notInList += 1;
			}
		}
		//checks if the word is correct
		if (userInput == secret)
		{
			std::cout << "Password Accepted." << '\n';
			//time delay allows the user to read the result before the console closes
			Sleep(3000);

			return 0;
		}

		//if a word not available is input, reset but don't count as an attempt
		if (notInList >= numberOfWords)
		{
			std::cout << "Invalid Word..." << '\n';
			notInList = 0;
		}

		//if not secret word, lower attempt var and calculate number of characters in guess and secret word
		//that are the same letter and in the same position
		else if (attempts > 0 && userInput != secret)
		{
			attempts -= 1;

			notInList = 0;

			std::cout << "Entry denied. " << "Likeness=" << CompareLikeness(userInput, secret) << '\n';
			std::cout << "Attempts remaining: " << attempts+1 << '\n';
		}

		//if the number of attempts reaches zero then game over
		else if (attempts == 0)
		{
			std::cout << "Terminal Locked. Password was: " << secret << ". Exiting...";
			//time delay allows the user to read the result before the console closes
			Sleep(3000);

			return 0;
		}
	}

	

	return 0;
}

	

