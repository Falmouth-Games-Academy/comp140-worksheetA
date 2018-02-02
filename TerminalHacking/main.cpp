// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"

const int wordLength = 5;
const int numberOfWords = 15;
const int numberOfLives = 4;

// Function Declarations
std::string guessWord(int numberOfLives);
std::string lengthCompare(std::string wordGuessed, std::string secret);
int likenessCheck(std::string wordGuessed, std::string secret);
int inList(std::set<std::string> options, std::string wordGuessed);

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

	std::cout << "Please type your guess and press enter." << std::endl;

	// Run until the players hits 0 lives
	// main game loop where other functions are called from
	int stillRunning = 0; // used to see if the game should still be running or if they have hit the number of lives
	while(stillRunning < numberOfLives)
	{
		std::string wordGuessed = guessWord((numberOfLives - stillRunning)); // passes argument number of lives minus the amount of tries taken already
		stillRunning++; //increments the counter
		int likeness = likenessCheck(wordGuessed, secret); // gets likeness score
		int isInList = inList(options, wordGuessed);
		if (isInList == 0)
		{
			stillRunning--; //decrements the counter
			std::cout << "Not in list, try again" << std::endl;
		}
		else if (likeness < secret.length())
		{
			std::cout << "Likeness score: " << likeness; // Print the likeness score from last guess
			if ((numberOfLives - stillRunning) > 0) // if player still has lives tell them to try again
			{
				std::cout << ". Try again" << std::endl;
			}
			else // if no more lives
			{
				std::cout << std::endl << "You ran out of lives, the police have been called." << std::endl << "Please wait for them to collect you." << std::endl;
			}
		}
		else // this is if they get the correct word
		{
			std::cout << std::endl << "Well done, you have entered the correct password!" << std::endl;
			break;
		}
	}

	return 0;
}

std::string guessWord(int numberOfLives)
{	// Requests a guess and shows how many lives remaining
	// Returns the guessed word
	std::string wordGuessed = "None";
	std::cout << "You have " << numberOfLives << " lives left" << std::endl;
	std::cin >> wordGuessed;
	for (int i = 0; i < wordGuessed.length(); i++) // loops through each letter of the entered word
	{
		wordGuessed[i] = (toupper(wordGuessed[i])); // makes current letter upper case
	}
	return wordGuessed;
}

std::string lengthCompare(std::string wordGuessed, std::string secret) // Used to check if one of the words is longer, then passed into likenessCheck to avoid
{																	   // crashing by trying to check a character that isnt there
	int compared = wordGuessed.length() - secret.length();
	if (compared < 0) // if wordGuessed is smaller than secret
	{
		return wordGuessed;
	}
	else if (compared > 0) // if wordGuessed is bigger
	{
		return secret;
	}
	else // if equal
	{
		return secret;
	}
}

int likenessCheck(std::string wordGuessed, std::string secret)
{	// Checks each position of the guessed word vs the secret word and returns the likeness score(matching letter and position)
	std::string shortestWord = lengthCompare(wordGuessed, secret);
	int likeness = 0;
	for (int i = 0; i < shortestWord.length(); i++)
	{
		//wordGuessed[i] = (toupper(wordGuessed[i])); // makes current letter upper case
		if (secret[i] == wordGuessed[i])
		{
			likeness++;
		}
	}
	return likeness;
}

// checks if the entered word is one in the list of options
int inList(std::set<std::string> options, std::string wordGuessed)
{
	int isInList = 0; // 0 for not in list, 1 for in list
	for each (std::string word in options)
	{
		if (word == wordGuessed)
		{
			isInList = 1;
		}
	}
	return isInList;
}

