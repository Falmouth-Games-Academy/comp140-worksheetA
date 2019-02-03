// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"
using namespace std;

int numberOfLives = 4;
int maxLikenessWordCount = 3;

const int wordLength = 5;
const int numberOfWords = 15;

bool guessed = false;

string guessedWord;
string secret;
set<string> options;

int CalculateLikeness(string word)
{
	int likeness = 0;
	//Go through each letter of the word
	for (int i = 0; i < word.length(); ++i)
	{
		//If the letters of both words at the current position are the same
		if (word.at(i) == secret.at(i))
		{
			//Increase the likeness by 1
			likeness += 1;
		}
	}
	return likeness;
}

void ChooseWords()
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
			//Randomly choose a word
			string chosenWord = words.getRandomWord();
			int chosenWordlikeness = CalculateLikeness(chosenWord);
			int LikenessWordCount = 0;
			//Compare the likeness of the chosen word with likeness of all words in options
			for each (string word in options)
			{
				int wordLikeness = CalculateLikeness(word);
				if (chosenWordlikeness == wordLikeness)
				{
					LikenessWordCount += 1;
				}
			}
			//If the number of words with the same likeness as the chosen word is less than the max limit, insert the word
			if(LikenessWordCount < maxLikenessWordCount)
				options.insert(chosenWord);
		}

		// Display all words
		for each (string word in options)
		{
			cout << word << endl;
		}
	}
}

int main()
{
	ChooseWords();

	//Input the guessed word
	cin >> guessedWord;

	//Convert any lowercase characters to uppercase
	for (basic_string<char>::iterator l = guessedWord.begin(); l != guessedWord.end(); l++)
	{
		*l = toupper(*l);
	}

	for each (string word in options)
	{
		if (guessedWord == word)
		{
			//If the guessed word is the secret word
			if (guessedWord == secret)
			{
				//Print a win message and reset the game
				cout << "Y O U   W I N" << endl;
				guessed = false;
				numberOfLives = 4;
				main();
				return 0;
			}
			//If the guessed word is not the secret word and the player has 1 or more lives
			else if (numberOfLives >= 1)
			{
				//Calculate the likeness of the guessed word to the secret word, subtract a life and reset the input
				int likeness = CalculateLikeness(guessedWord);
				cout << "Likeness: " << likeness << endl;
				cout << "You have " << numberOfLives << " lives left." << endl;
				guessed = true;
				numberOfLives -= 1;
				main();
				return 0;
			}
			//If the guessed word is not the secret word and the player has 0 lives left
			else
			{
				//Print a game over message and reset the game
				cout << "G A M E	O V E R" << endl;
				guessed = false;
				numberOfLives = 4;
				main();
				return 0;
			}
		}
	}

	//If none of the conditions above are met, print an invalid guess message and reset the input
	cout << "Invalid Guess" << endl;
	guessed = true;
	main();
	return 0;
}