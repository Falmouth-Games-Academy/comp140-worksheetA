// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"
//#include <string>
#include <algorithm>
#include <map>

const int wordLength = 5;
const int numberOfWords = 15;

int Calculate_Likeness(std::string secretWord, std::string guessWord)
{
	int likeness = 0;
	for (int i = 0; i < wordLength; i++) 
		secretWord[i] == guessWord[i] ? likeness++ : true; // if the letters match, increase likeness. Else do nothing
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

	std::map<int, int> word_tally = { {0,0},{1,0},{2,0},{3,0},{4,0} };

	while (options.size() < numberOfWords)
	{
		std::string word = words.getRandomWord();
		int likeness = Calculate_Likeness(secret, word); // gets the likeness between word and likeness
		if (word_tally[likeness] < 4) { // if there are more 4 words of the same likeness already, dont add this word.
			options.insert(word);
			word_tally[likeness] = word_tally[likeness] + 1;
		}
	}

	// Display all words
	for each (std::string word in options)
	{
		std::cout << word << std::endl;
	}

	int lives = 4;
	std::string guess;
	bool valid;
	bool success = false;

	do {
		valid = false;
		while (!valid) { // get input until guess is valid
			std::cout << "Enter your Guess..." << std::endl;
			std::getline(std::cin, guess);
			std::transform(guess.begin(), guess.end(), guess.begin(), ::toupper); // automatically converts guess to upper case - taken from online
			for (auto i : options)
				if (i == guess ) valid = true; // if guess is equal to one of the options, valid becomes true; else is stays false.
			if (!valid) std::cout << "Invalid guess" << std::endl;
		}	
		if (guess == secret) {
			success = true;
		}
		else {
			std::cout << "Likeness between guess and secret word is " << Calculate_Likeness(secret, guess) << std::endl;
			lives--;
		}
	} while (lives > 0 && !success); // iterate while player has lives or hasnt guessed correctly
	success ? std::cout << "You win!" : std::cout << "You lose!";

	return 0;
}
