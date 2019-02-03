 // main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"
#include <stdlib.h>

int wordLength; //2 min - 14 max
const int numberOfWords = 15;
int lives = 4;
std::string PlayerInput;
bool PlayAgain = true;

std::string WordCheck(std::string word) 
{
	for (int i = 0; i < word.length(); i++)
	{
		if (isalpha(word[i])) word[i] = toupper(word[i]);
		else break;
	}
	return word;
}

void Replay() {
	bool RePlay = true;
	while (RePlay) 
	{
		std::cout << std::endl << "Do you wanna play again? YES or NO" << std::endl;
		std::cin >> PlayerInput;
		PlayerInput = WordCheck(PlayerInput);
		if (PlayerInput == "YES") 
		{
			RePlay = false;
			lives = 4;
			wordLength = 0;
		}
		else if (PlayerInput == "NO")
		{
			RePlay = false;
			PlayAgain = false;
		}
		else std::cout << "Invalid Input" << std::endl;
	}
	
}

int main()
{
	while (PlayAgain){
		system("CLS");
		while (wordLength == 0)
		{
			std::cout << "Select difficulty: EASY, NORMAL, HARD." << std::endl;
			std::cin >> PlayerInput;
			PlayerInput = WordCheck(PlayerInput);
			if (PlayerInput == "EASY") wordLength = 4;
			else if (PlayerInput == "NORMAL") wordLength = 6;
			else if (PlayerInput == "HARD") wordLength = 8;
			else
			{
				wordLength = 0;
				std::cout << "Invalid Input" << std::endl << std::endl;
			}

		}

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



		// TODO: implement the rest of the game

		std::cout << std::endl << "Find a secret word, type in word from a list:" << std::endl;

		// Display all words
		for each (std::string word in options)
		{
			std::cout << word << std::endl;
		}

		while (lives > 0) {

			std::cout << std::endl << "You have " << lives << " tries left." << std::endl;
			std::cin >> PlayerInput;

			PlayerInput = WordCheck(PlayerInput);



			bool CorrectWord = false;

			for each (std::string word in options)
			{
				if (PlayerInput == word) {
					CorrectWord = true;
					break;
				}
			}

			if (!CorrectWord) {
				std::cout << "Invalid Guess" << std::endl;
			}
			else if (PlayerInput == secret)
			{
				std::cout << std::endl << "You Win!" << std::endl;
				Replay();
				break;
			}
			else
			{
				int Likeliness = 0;
				for (int i = 0; i < PlayerInput.length(); i++)
				{
					if (PlayerInput[i] == secret[i]) Likeliness++;
				}
				std::cout << Likeliness << " Letters are in correct position." << std::endl;
				lives--;
			}
		}
		if (lives == 0) {
			std::cout << std::endl << "You Loose!" << std::endl;
			Replay();
		}

	}
	
	return 0;
}