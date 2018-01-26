// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"
#include <cstdlib>
#include <windows.h>
#include "TerminalHackingUtils.h"
#include "random"

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
	int tries = 4;

	std::string userInput;
	std::string secretWord;

	while (running)
	{
		std::cin >> userInput;
		MakeWordUppercase(userInput);
		
		if (userInput != secret && tries >  0)
		{
			tries -= 1;
			int correctLetters=CheckCorrrectLetters(userInput, secret);

			std::cout << "INCORECT PASSWORD - ACCESS DENIED" << correctLetters
				 << "/5" << std::endl;

		}
		else if (userInput == secret)
		{
			std::cout << "CORRECT PASSWORD - ACCESS GRANTED" << std::endl;
			StreamlineOfRandomChars();
			Sleep(3000);
			running = false;
		}

		if (tries == 0)
		{
			Sleep(500);
			std::cout << "-ERROR- NO MORE ATTEMPTS ALLOWED - SHUTTING DOWN";
			Sleep(2000);
			running = false;
		}
	}

	return 0;
}
//Chapter 6 - Refrences(tic-tac-toe)
void MakeWordUppercase(std::string& word)
{
	for (char& c : word) c = toupper(c);
}

int CheckCorrrectLetters(std::string& word, std::string& secret)
{
	int correctLetters = 0;
	int numberOfLetters = word.length();

	for (int i = 0; i < numberOfLetters; i++)
	{
		if (word[i] == secret[i])
		{
			correctLetters++;
		}
	}

	return correctLetters;
}

int StreamlineOfRandomChars()
{
	int numerbOfchars = 1200;

	while (numerbOfchars != 0)
	{
		char asciiValue = RandInt(33, 90);
		std::cout << asciiValue;
		Sleep(8);
		numerbOfchars -= 1;
	}

	std::cout << "END OF ENCRYPTED MESSAGE - SHUTTING DOWN";
	return 0;
}