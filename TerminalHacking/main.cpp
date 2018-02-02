// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"

const int wordLength = 5;
const int numberOfWords = 15;
const int numberOfLives = 4;

std::string guessWord(int numberOfLives)
{	// Requests a guess and shows how many lives remaining and returns the guessed word
	std::string wordGuessed = "None";
	std::cout << "Please type your guess and press enter." << std::endl;
	std::cout << "You have " << numberOfLives << " lives left" << std::endl;
	std::cin >> wordGuessed;
	return wordGuessed;
}

std::string lengthCompare(std::string wordGuessed, std::string secret) 
// Used to check if one of the words is longer, then passed into likenessCheck to avoid
// crashing by trying to check a character that isnt there
{																	   
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
{	// Checks each position of the guessed word vs the secret word
	// returns the likeness score(matching letter and position)
	std::string shortestWord = lengthCompare(wordGuessed, secret);
	int likeness = 0;
	for (int i = 0; i < shortestWord.length(); i++)
	{
		// makes current letter upper case
		wordGuessed[i] = (toupper(wordGuessed[i])); 
		if (secret[i] == wordGuessed[i])
		{
			likeness++;
		}
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

	// Run until the players hits 0 lives
	// main game loop where other functions are called from
	for (int i = 0; i < numberOfLives; i++)
	{
		std::string wordGuessed = guessWord((numberOfLives - i)); // passes argument number of lives minus the amount of tries taken already
		int likeness = likenessCheck(wordGuessed, secret); // gets likeness score
		if (likeness < secret.length())
		{
			std::cout << "------------------------------------------" << std::endl; // used just to seperate the last try in the command line
			for each (std::string word in options) // print the list of options again
			{
				std::cout << word << std::endl;
			}
			std::cout << "Likeness score: " << likeness << std::endl; // Print the likeness score from last guess
			if ((numberOfLives - i) > 1) // if player still has lives tell them to try again
			{
				std::cout << "Give it another try!" << std::endl;
			}
			else // if no more lives
			{
				std::cout << "You ran out of lives, the police have been called." << std::endl << "Please wait for them to collect you." << std::endl;
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