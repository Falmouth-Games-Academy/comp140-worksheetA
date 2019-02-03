// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"
#include <string>

const int wordLength = 5;
const int numberOfWords = 15;

int calc_likeness(std::string choice, std::string word)
{
	int likeness = 0;

	for (int i = 0; i < word.length(); i++)
	{
		if (choice[i] == word[i])
			likeness++;
	}
	return likeness;
}

int main()
{
	// Initialise variable for playing again once the game ends
	char playAgain = ' ';
	do {
		playAgain = ' ';

		// Seed the random number generator with the current time,
		// to ensure different results each time the program is run

		srand(static_cast<unsigned int>(time(nullptr)));

		// Initialise word list
		WordList words(wordLength);

		// Choose secret word
		std::string secret = words.getRandomWord();

		// Create a set to hold the list of options
		std::set<std::string> options;

		// Create a vector to hold the words that don't fit the difficulty criteria
		std::vector<std::string> checked_words;

		// Put the secret word in the set
		options.insert(secret);

		// Input difficulty: 1 - EASY, 2 - MEDIUM, 3 - HARD
		int difficulty = 0;
		do
		{
			// Prompt the user for the desired difficulty of the game
			std::cout << "Please input desired difficulty: 1 for EASY, 2 for MEDIUM and 3 for HARD\n";
			std::cin >> difficulty;

		} while (difficulty < 1 || difficulty > 3);

		// Fill the set with more words
		// Using a set for options guarantees that the elements are all different
		while (options.size() < numberOfWords)
		{
			// TODO: implement difficulty algorithm
			std::string word = words.getRandomWord();
			checked_words.insert(checked_words.end(), word);
			options.insert(word);
		}

		// Display all words
		for each (std::string word in options)
		{
			std::cout << word << std::endl;
		}

		int lives = 4;
		bool word_was_guessed = false;

		while (lives > 0 && word_was_guessed == false)
		{
			std::string choice;

			std::cout << "Choose a word:\n";
			std::cin >> choice;

			for (int i = 0; i < choice.length(); i++)
			{
				choice[i] = toupper(choice[i]);
			}

			bool word_in_options = false;

			for each (std::string word in options)
			{
				if (word == choice)
				{
						
					word_in_options = true;
					break;
				}
			}

			if (word_in_options == false)
			{
				std::cout << "Invalid guess!\n";
				continue;	// return to start without decrementing lives
			}
			else
				lives--;	// if the word is valid, decrement lives 

			if (choice == secret)
				word_was_guessed = true;
			else
				std::cout << "Likeness: " << calc_likeness(choice, secret) << "\nLives remaining: " << lives << "\n";
		}

		if (word_was_guessed == true)
			std::cout << "You win!\n";
		else
			std::cout << "You lose, the word was " << secret << "\n";

		std::cout << "Play again? y/n\n";
		std::cin >> playAgain;
		while (playAgain != 'y' && playAgain != 'n')
		{
			std::cout << "Invalid input, please try again: y/n\n";
			std::cin >> playAgain;
		}
	} while (playAgain == 'y');
	return 0;
}
