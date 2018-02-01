// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"

const int wordLength = 5;
const int numberOfWords = 15;
int numberOfLives = 4;
int intNumRight;
std::string strGuess;

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
	//This while loop checks to see if you stil have lives and if so lets you make a guess
	while (numberOfLives > 0)
	{
		std::cout << "Number of Lives" << numberOfLives << std::endl;
		std::cin >> strGuess;
		//checks to see if your guess is correct
		if (strGuess == secret)
		{
			std::cout << "Congrats, you win!" << std::endl;
			std::cin.ignore();
			break;
		}
		else
		{
			//this is checking how many letters are the same in the guessed word compared to the secret word 
			intNumRight = 0;
			for (int i = 0; i < (wordLength - 1); i++)
			{
				if (secret[i] == strGuess[i])
				{
					intNumRight++;
				}
			}
			//if your guess is wrong then take away one life and then let you guess again, baby
			std::cout << "Wrong" << intNumRight << "/" << wordLength << std::endl;
			numberOfLives--;
			// if your lifes are equal to zero then you loss, wanker
			if (numberOfLives == 0)
			{
				std::cout << "Game Over" << std::endl;
				std::cin.ignore();
			}
		}
	}
	std::cin.ignore();
	return 0;
}