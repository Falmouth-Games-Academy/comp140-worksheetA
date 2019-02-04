#pragma once

class WordList
{
public:
	WordList(int wordLength);
	int secretWordIndex = 0;	// Use as a reference when looking up random words

	std::string getRandomWord();	//	Difficulty determines the range we'll be looking for words in

private:
	std::vector<std::string> words;
};