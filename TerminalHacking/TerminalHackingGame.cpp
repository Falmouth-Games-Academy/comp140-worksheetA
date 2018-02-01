#include <cstdlib>
#include <windows.h>

#include "stdafx.h"
#include "WordList.h"
#include "TerminalHackingUtils.h"

const int wordLength = 5;
const int numberOfWords = 15;

int TheGame()
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

	//running bool to keep the application running
	bool running = true;

	//the amount of tries/attemtps the player gets to guess the secret word
	int tries = 4;

	//string variables for the User Input
	std::string userInput;

	//Shows the player that they need to enter a password/secret word
	std::cout << "--ENTER PASSWORD--" << std::endl;

	//the main game running loop
	while (running)
	{
		//takes in the user's input
		std::cin >> userInput;

		//Makes the user's input all caps
		MakeWordUppercase(userInput);

		//check the User Input against the secret word
		if (userInput != secret && tries > 0)
		{
			tries -= 1;
			int correctLetters = CheckCorrrectLetters(userInput, secret);

			std::cout << "INCORRECT PASSWORD - ACCESS DENIED " << correctLetters
				<< "/5" << std::endl;

		}

		//If the player guesses the right word print out reward and end the game
		else if (userInput == secret)
		{
			std::cout << "CORRECT PASSWORD - ACCESS GRANTED " << std::endl;
			std::cout << "--NOW PRINTING ENCRYPTED MESSAGE--" << std::endl;
			StreamlineOfRandomChars();
			Sleep(3000);
			return running = false;
		}

		//if the player runs out of attempts end the game
		if (tries == 0)
		{
			Sleep(500);
			std::cout << "-ERROR- NO MORE ATTEMPTS ALLOWED - SHUTTING DOWN";
			Sleep(2000);
			return running = false;
		}
	}

	return 0;
}

//Function that converts a string to caps
//using a for loop that goes throught each charachter in a string and converts them using "toupper"
void MakeWordUppercase(std::string& word)
{
	for (char& c : word) c = toupper(c);
}

//Function the checks the User Input against the secret word
//It will then return the amount of charachters that are in the right position
int CheckCorrrectLetters(std::string& word, std::string& secret)
{
	int correctLetters = 0;
	const int numberOfLetters = word.length();

	for (int i = 0; i < numberOfLetters; i++)
	{
		if (word[i] == secret[i])
		{
			correctLetters++;
		}
	}

	return correctLetters;
}

//creates a stream of random charachters acting as a 
//fake encrypted message to reward the player for guessing the secret word
int StreamlineOfRandomChars()
{
	//the number of random chars that will be rpinted out
	int numerbOfchars = 1200;
	int RandInt = rand() % 33 + 90;

	//while loop that will print out the random cahrs
	while (numerbOfchars != 0)
	{
		char asciiValue = RandInt;
		std::cout << asciiValue;
		Sleep(8);
		numerbOfchars -= 1;
	}

	std::cout << "END OF ENCRYPTED MESSAGE - SHUTTING DOWN";
	return 0;
}