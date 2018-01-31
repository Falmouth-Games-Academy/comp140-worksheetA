#pragma once
#include "stdafx.h"

//Converts a string to upper 
void MakeWordUppercase(std::string& word);


int CheckCorrrectLetters(std::string& word, std::string& secret);

int StreamlineOfRandomChars();

int RandInt(int A, int B)
{
	return (rand() % B + A);
}
