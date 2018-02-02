#include "stdafx.h"
#include "WordList.h"
#include <windows.h>
#include <ctype.h>
#include "main.h"




//function that takes a string and applies the toupper function to each character
std::string MakeUppercase(std::string userInput)
{
	for (int i = 0; i < userInput.size(); i++)
	{
		userInput.at(i) = toupper(userInput.at(i));
	}
	return userInput;
}

//function that compares the characters in two strings and increases the likeness value
//when two characters in the same position are equal
int CompareLikeness(const std::string userInput, const std::string secret)
{
	int wordLikeness = 0;

	for (int i = 0; i < wordLength; ++i)
	{
		if (userInput[i] == secret[i])
		{
			wordLikeness += 1;
		}
	}
	return wordLikeness;
}