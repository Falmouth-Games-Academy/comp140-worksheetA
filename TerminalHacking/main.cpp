// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"
#include <iostream>
#include <string>

using namespace std;

const int wordLength = 5;
const int numberOfWords = 15;


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

	//-------------------------------------------------------------------------------------------------------------------

	/* 1) Declare the local int CorrectLetterNum to store the value of the letters contained within the password and the user guess.
	2)Declare a string array to store the user input --(called UserGuess) and declare a string to store the password word
	taken from the word list.
	3)The int 'attempt' is declared and set with the max value of 4 
	((I have only used block commenting here to differentiate between Brain's and my own comments*/

	
	int CorrectLetterNum = 0;
	int attempts = 4;
	string UserGuess; 
	string SelectedPassword=secret;//Secret linked to new string
	string answer;
	
	
	/* Display a prompt to the user to input a password and store the input in a string*/

    
	cout << "IN CAPITALS ONLY! INPUT USER PASSWORD:   " << endl;

		do {  //the main section sits within a do while loop
		cin >> UserGuess;// add toupper here
		attempts--;    //this local variable will decrease with each iteration of the loop

		/*This ssection uses a whole word comparison to check to see if the userGuess is the same as the password, if so, the programme can end here */

		if (UserGuess == SelectedPassword)
		{
			cout << "ACCESS GRANTED" << endl;
			cout << "You've won!" << endl;
			break;
		}
		else
		{
			/*This section compares the individual letters of UserGuess and SelectedPasssword against each other. This for loop iterates
			through the array comparing each letter according to the length of the word*/

			for (int i = 0; i < SelectedPassword.length(); i++)
			{
				for (int j = 0; j < UserGuess.length(); j++) {
					if (SelectedPassword[i] == UserGuess[j])
					{
						CorrectLetterNum++;  //if a letter is shared by both strings, the int 'correctletter' increases in value by one
					}
				}
			}

			cout << "ACCESS DENIED" << endl;
			cout << "You have  " << CorrectLetterNum << "  matching letters out of " << SelectedPassword.length() << endl;
			cout << "Would you like to try again? <Y>/<N> ? ";
				cin >> answer;

			if (answer == "y" || answer == "Y") //this section provides the user with the option to continue or not with the game
			{
				cout << "You have " << attempts << "  attempts remaining" << endl;
				CorrectLetterNum = 0;//This resets the correctLetter variable to zero, so that correct letters do not accumulate with each new try
			}

			if (answer == "n" || answer == "N")
			{
				cout << "Game Over" << endl;
				break;

			}
		}

        } while (UserGuess != SelectedPassword && attempts > 0); //while the conditions of the 'do while' loop is not met, the loop will continue.

		cout << "Game Over" << endl;
		system("pause");

		return 0;

}
				