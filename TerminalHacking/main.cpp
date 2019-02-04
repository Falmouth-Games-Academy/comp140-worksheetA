// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"
#include <random>
#include <string>

const int wordLength = 5;
const int numberOfWords = 15;
const bool unique_words = true;		// Set to false if player can guess the same word multiple times (and consequently lose lives each time)

float medianLikeness;

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

// Returns a word from the word list based on a given likeness score
std::string findWord(int likeness, std::string secretWord, WordList words)
{
	medianLikeness += likeness;
	std::string word = "";
	do
	{
		word = words.getRandomWord();

	} while (calc_likeness(word, secretWord) != likeness);
	return (word);
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

		// Create a vector to hold the guessed words
		std::set<std::string> guessed_words;

		// Put the secret word in the set
		options.insert(secret);

		// Input difficulty: 1 - EASY, 2 - MEDIUM, 3 - HARD
		int difficulty = 0;
		do
		{
			// Prompt the user for the desired difficulty of the game
			std::cout << "Please input desired difficulty: 1 for EASY, 2 for MEDIUM and 3 for HARD\n";
			std::cin >> difficulty;

		} while ((difficulty < 1 || difficulty > 3));	// Make sure 

		difficulty = wordLength - difficulty;
		

		// Setup for generating random number within given range
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator for generating a range of difficulties
		std::uniform_int_distribution<> distr(fmax(0, difficulty - 2), fmin(wordLength - 2, difficulty + 1)); // define the range for likeness: 1 more or less than the difficulty

		// Fill the set with more words
		// Using a set for options guarantees that the elements are all different
		while (options.size() < numberOfWords)
		{
			// Insert a random word that matches the given likeness score (difficulty)
			options.insert(findWord(distr(eng), secret, words));
		}

		std::cout << "Median Likeness is " << medianLikeness / 15 << "\n";

		// Display all words
		for each (std::string word in options)
		{
			std::cout << word << std::endl;
		}

		int lives = 4;
		bool word_was_guessed = false;

		while (lives > 0 && word_was_guessed == false)
		{
			std::string player_word = "";

			// Keep asking for input until the player chooses a new word
			do
			{
				if (player_word != "")
				{
					std::cout << "You already tried guessing that word!\n";
				}

				std::cout << "Choose a word:\n";
				std::cin >> player_word;

				for (int i = 0; i < player_word.length(); i++)
				{
					player_word[i] = toupper(player_word[i]);
				}
			} while (guessed_words.find(player_word) != guessed_words.end() && unique_words == true);

			guessed_words.insert(player_word);

			// Search for player word within options
			bool word_in_options = false;
			
			for each (std::string word in options)
			{
				if (word == player_word)
				{
						
					word_in_options = true;	// Stop searching if word was found
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

			if (player_word == secret)
				word_was_guessed = true;
			else
				std::cout << "Likeness: " << calc_likeness(player_word, secret) << "\nLives remaining: " << lives << "\n";
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
