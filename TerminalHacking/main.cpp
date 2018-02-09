// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"

const int wordLength = 5;
const int numberOfWords = 15;
const int numberOfLikeWords = 5;
const int lengthOfLikeness = 2;
const int findAttempts = 10;

int numberOfLives = 4;

int GetLikeness(std::string GuessedWord, std::string SecretWord)
{
	int LikenessScore = 0;
	for (int i = 0; i < wordLength; i++)
	{
		try
		{
			if (GuessedWord[i] == SecretWord[i])
			{
				LikenessScore++;
			}
		}
		catch(std::exception)  //Catches if the two words are not the same length *todo: update to correct exception
		{
			break;
		} 
	}
	return LikenessScore;
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
	while (options.size() < numberOfWords - numberOfLikeWords)
	{
		std::string word = words.getRandomWord();
		options.insert(word);
	}
	while (options.size() < numberOfWords)
	{
		std::string word = words.getLikeWord(secret, lengthOfLikeness, findAttempts);
		options.insert(word);
	}

	// Display all words
	for each (std::string word in options)
	{
		std::cout << word << std::endl;
	}
	std::string Guess = "              ";
	for (; numberOfLives > 0; numberOfLives--)
	{
		bool GuessInList = false;
		
		while (!GuessInList)
		{
			std::cout << "Please Enter Your Guess" << std::endl;
			std::getline(std::cin, Guess);
			for (int i = 0; i < Guess.length(); i++)
			{
				Guess[i] = toupper(Guess[i]);
			}
			if (options.find(Guess) != options.end())
			{
				GuessInList = true;
			}
			else
			{
				std::cout << "Please Enter One Of The Words Above" << std::endl;
			}
		}
		int Likeness = GetLikeness(Guess, secret);
		if (Likeness == secret.length())
		{
			std::cout << "You Win!!";
			std::getline(std::cin, Guess);
			return 0;
		}
		else
		{
			std::cout << "Likeness: " << Likeness << std::endl;
			std::cout << "Number Of Lives: " << numberOfLives << std::endl;
		}
	}
	std::cout << "You Lose :(";
	std::getline(std::cin, Guess);
	return 0;
}
