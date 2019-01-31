// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"
using namespace std;

const int wordLength = 5;
const int numberOfWords = 15;
int numberOfLives = 4;
string guessedWord;
bool guessed = false;

set<string> options;
string secret;

int main()
{
	if (!guessed)
	{
		// Seed the random number generator with the current time,
		// to ensure different results each time the program is run
		srand(static_cast<unsigned int>(time(nullptr)));

		// Initialise word list
		WordList words(wordLength);

		// Choose secret word
		secret = words.getRandomWord();

		// Reset the set that holds the list of options
		options.clear();

		// Put the secret word in the set
		options.insert(secret);

		// Fill the set with more words
		// Using a set for options guarantees that the elements are all different
		while (options.size() < numberOfWords)
		{
			string word = words.getRandomWord();
			options.insert(word);
		}

		// Display all words
		for each (string word in options)
		{
			cout << word << endl;
		}
	}

	// TODO: implement the rest of the game

	cin >> guessedWord;

	for (basic_string<char>::iterator l = guessedWord.begin(); l != guessedWord.end(); l++)
	{
		*l = toupper(*l);
	}

	for each (std::string word in options)
	{
		if (guessedWord == word)
		{
			if (guessedWord == secret)
			{
				std::cout << "Y O U   W I N" << std::endl;
				guessed = false;
				numberOfLives = 4;
				main();
				return 0;
			}
			else if(numberOfLives > 1)
			{
				int likeness = 0;
				for (int i = 0; i<guessedWord.length(); ++i)
				{
					if (guessedWord.at(i) == secret.at(i))
					{
						likeness += 1;
					}
				}
				std::cout << "Likeness: " << likeness << std::endl;
				guessed = true;
				numberOfLives -= 1;
				main();
				return 0;
			}
			else
			{
				std::cout << "G A M E	O V E R" << std::endl;
				guessed = false;
				numberOfLives = 4;
				main();
				return 0;
			}
		}
	}

	std::cout << "Invalid Guess" << std::endl;
	guessed = true;
	main();

	return 0;
}
