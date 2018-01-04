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

	return 0;
}

std::string inputEnter;
bool Active = true;
int NumTries = 5;

	//This takes in the number of tries paramiter as a console output
	std::cout << "Secret word?" << numTries << std::endl;


while (Active)
{
	//Reads the input
	std::cin >> inputEnter;

	//Checks the Attempt against the secret word and tries
	if (strAttempt != secret && tries >  0)

	//If the attempt has less than or equal to 1 
	NumTries -= 1;
	int RightLetters = CheckRightLetters(strAttempt, secret);

	std::cout << "The word is incorrect, no access for you! You have commited crimes against Skyrim and its people (50) Bounty added" << correctLetters << "/5" << std::endl;

}
else if (userInput == secret)
{
	std::cout << "The password is correct, congratulations! Now you don't have to pay the bounty, yay for virtual crime. " << std::endl;
	Active = false
}







