#pragma once
#include "stdafx.h"

//The game function that will run the game in the console in main.cpp
int TheGame();

//Converts a string to upper 
void MakeWordUppercase(std::string& word);

bool CheeckIfWordIsCorrect(std::string userInput, std::string secret, bool running, int tries);

int CheckCorrrectLetters(std::string& word, std::string& secret);

int StreamlineOfRandomChars();
