#pragma once

class WordList
{
public:
	WordList(int wordLength);

	std::string getRandomWord();

	// Picks a secret word from a set of words based on their likeness score to the rest of the set of words
	std::string getSecretWord(const std::set<std::string> &options, unsigned int minLikness, unsigned int maxLikeness, unsigned int matchPercentage);

	// Returns true if the word is found within the list
	bool containsWord(const std::set<std::string> &options, std::string &word);

	// Returns the number of letters which line up across both words
	int getLikness(std::string &secret, std::string &guess);

private:
	std::vector<std::string> words;
};