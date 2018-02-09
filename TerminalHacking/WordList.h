#pragma once

class WordList
{
public:
	WordList(int wordLength);

	std::string getRandomWord();
	std::string WordList::getLikeWord(std::string Secret, int Likeness, int FindAttempts);

private:
	std::vector<std::string> words;
};