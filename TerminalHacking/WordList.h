#pragma once

class WordList
{
public:
	WordList(int wordLength);

	std::string getRandomWord();

	bool containsWord(std::string word);

private:
	std::vector<std::string> words;
};