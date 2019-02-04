#pragma once

class WordList
{
public:
	WordList(int wordLength);

	std::string getRandomWord();
	static int getLikeness(std::string generatedWord, std::string playerWord);
private:
	std::vector<std::string> words;
};