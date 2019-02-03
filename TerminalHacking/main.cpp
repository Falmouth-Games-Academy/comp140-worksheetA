 // main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WordList.h"
#include <stdlib.h>

//LIST OF VARIABLES.
bool PlayTheGame = true;
int Lives = 4;
int WordsLength = 0; //2 min - 14 max
const int NumberOfWords = 15;
int WordLikelinesses[] = { 5, 3, 3, 3, 0, 0, 0, 0, 0};
int WordLikelinessesDefault[] = { 5, 3, 3, 3, 0, 0, 0, 0, 0 };
std::string PlayerInput;
std::string SecretWord;
std::set<std::string> ListOfWords;

//FUNCTION UPERCASES WORD
std::string InputToUpperCase(std::string word) 
{
	for (int i = 0; i < word.length(); i++)
	{
		if (isalpha(word[i])) 
		{
			word[i] = toupper(word[i]);
		}
		else break;
	}
	return word;
}

//MAKES PLAYER CHOOSE GAME DIFFICULTY.
void DifficultySelection() {
	while (WordsLength == 0)
	{
		std::cout << "Select difficulty: EASY, NORMAL, HARD." << std::endl;
		std::cin >> PlayerInput;
		PlayerInput = InputToUpperCase(PlayerInput);
		if (PlayerInput == "EASY") WordsLength = 4;
		else if (PlayerInput == "NORMAL") WordsLength = 6;
		else if (PlayerInput == "HARD") WordsLength = 8;
		else
		{
			std::cout << "Invalid Input" << std::endl << std::endl;
		}

	}
}

//FUNCTION SETS UP LIST OF WORDS
void WordListSetup() {
	// Seed the random number generator with the current time,
		// to ensure different results each time the program is run
	srand(static_cast<unsigned int>(time(nullptr)));

	// Initialise word list
	WordList words(WordsLength);

	// Choose secret word
	SecretWord = words.getRandomWord();
	

	// Put the secret word in the set
	ListOfWords.insert(SecretWord);

	// Fill the set with more words
	// Using a set for options guarantees that the elements are all different
	while (ListOfWords.size() < NumberOfWords)
	{
		std::string word = words.getRandomWord();
		int Likeliness = 0;
		for (int i = 0; i < word.length(); i++)
		{
			if (word[i] == SecretWord[i]) Likeliness++;
		}


		if (WordLikelinesses[Likeliness] > 0) 
		{
			ListOfWords.insert(word);
			WordLikelinesses[Likeliness]--;
		}
	}
}

//FUNCTION PRINTS OUT GAME INSTRUCTION AND LIST OF WORDS.
void PrintWords() {
	std::cout << std::endl << "Find a secret word, type in word from a list:" << std::endl;

	for each (std::string word in ListOfWords)
	{
		std::cout << word << std::endl;
	}
}

//FUNCTION TAKES PLAYER'S INPUT AND SAVES IT IN A VARIABLE TO BE CHECKED.
void PlayerGuess() {
	std::cout << std::endl << "You have " << Lives << " tries left." << std::endl;
	std::cin >> PlayerInput;
	PlayerInput = InputToUpperCase(PlayerInput);
}

//FUNCTION CHECKS WHETHER WORD IS INSIDE OF LIST OF WORDS AND WHETHER IT IS A SECRET WORD.
std::string InputCheck() {

	bool CorrectWord = false;

	for each (std::string word in ListOfWords)
	{
		if (PlayerInput == word) {
			CorrectWord = true;
			break;
		}
	}

	if (!CorrectWord) {
		return "WRONG WORD";
	}
	else if (PlayerInput == SecretWord)
	{
		
		return "GUESSED";
	}
	else
	{
		return "NOT GUESSED";
	}
	
}

//FUNCTION CHECKS AND PRINTS AMOUNT OF LETTERS SIMILAR TO ONES IN THE SECRET WORD.
void LikelinessCheck() {
	int Likeliness = 0;
	for (int i = 0; i < PlayerInput.length(); i++)
	{
		if (PlayerInput[i] == SecretWord[i]) Likeliness++;
	}
	std::cout << Likeliness << " letters are in correct position." << std::endl;
	Lives--;
}

//RESETS VARIABLES AND RESTERTS THE GAME IF PLAYER WANTS TO PLAY AGAIN.
void Replay() {
	bool RePlay = true;
	while (RePlay) 
	{
		std::cout << std::endl << "Do you wanna play again? YES or NO" << std::endl;
		std::cin >> PlayerInput;
		PlayerInput = InputToUpperCase(PlayerInput);
		if (PlayerInput == "YES") 
		{
			RePlay = false;
			Lives = 4;
			WordsLength = 0;
			ListOfWords.clear();
			for (int i = 0; i < (sizeof(WordLikelinesses) / sizeof(*WordLikelinesses)); i++)
			{
				WordLikelinesses[i] = WordLikelinessesDefault[i];
			}
		}
		else if (PlayerInput == "NO")
		{
			RePlay = false;
			PlayTheGame = false;
		}
		else std::cout << "Invalid Input" << std::endl;
	}
	
}

//MAIN LOOP OF THE GAME
int main()
{
	while (PlayTheGame){	
		system("CLS");							//Clears terminal after restarting the game.
		DifficultySelection();					//Makes player choose difficulty of the game.
		WordListSetup();						//Sets up secret word and word list.
		PrintWords();							//Prints instructions and word list.
		while (Lives > 0) {						//Guessing loop.
			PlayerGuess();						//Player makes a guess.
			std::string result = InputCheck();	//Guess is being checked.
			if(result == "WRONG WORD"){			//If wrong input, inform the player.
				std::cout << "Invalid Guess" << std::endl;
			}
			else if (result == "GUESSED") {		//If guessed secret word, say so, ask player for the next go and break this loop.
				std::cout << std::endl << "You have guessed the secret word. You Win!" << std::endl;
				Replay();
				break;
			}
			else if (result == "NOT GUESSED") {	//If not guessed, show how many letters are in correct position. 
				LikelinessCheck();
			}

			
		}
		if (Lives == 0) {						//If out of lifes, say that player lost, ask player for the next go.
			std::cout << std::endl << "You have not guessed the secret word. You Loose!" << std::endl;
			Replay();
		}

	}
	
	return 0;									//When loop is being broken, stops the game.
}