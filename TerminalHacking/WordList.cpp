#include "stdafx.h"
#include "WordList.h"

const std::string wordFileName("words.txt");

WordList::WordList(int wordLength)
{
	std::ifstream wordFile(wordFileName);
	std::string word;

	// Read past the copyright notice at the top of words.txt
	while (std::getline(wordFile, word) && word != "---")
	{
		// do nothing
	}

	// Read each line in the file
	while (std::getline(wordFile, word))
	{
		if (word.length() == wordLength)
		{
			// Scan through the line, converting each character to upper case.
			// If a non-alphabet character is encountered, reject the word.
			bool isValid = true;
			for (int i = 0; i < word.length(); i++)
			{
				if (isalpha(word[i]))
				{
					word[i] = toupper(word[i]);
				}
				else
				{
					isValid = false;
					break;
				}
			}

			// If it's a good word, add it to the list.
			if (isValid)
			{
				words.push_back(word);
			}
		}
	}
}

/*
	Clamps the value between the minimum and maximum
*/
int clamp(double value, double min, double max) {
	return (int)fmin(max, fmax(value, min));
}

std::string WordList::getRandomWord()
{
	int index = rand() % words.size();
	return words[index];
}

/*
	Returns a random word which has been chosen based on its likeness score to its fellow words
*/
std::string WordList::getSecretWord(std::set<std::string> options, unsigned int minLikeness = 2, unsigned int maxLikeness = 6, unsigned int matchPercentage = 10)
{
	std::string baseWord = "";
	for (std::string f : options) {
		baseWord = f;
		break;
	}
	// Clamp the values to keep them within range
	minLikeness = clamp(minLikeness, 0, baseWord.size());
	maxLikeness = clamp(minLikeness, 0, baseWord.size());
	matchPercentage = clamp(matchPercentage, 0, 100);
	
	std::vector<std::string> viable;
	int notMatched, likeness, percentage = 0;
	int wordsSize = options.size();

	for (unsigned int i = 0; i < wordsSize; i++)
	{
		notMatched = 0;
		for (unsigned int j = 0; j < wordsSize; j++)
		{
			likeness = getLikness(words[i], words[j]);
			if (likeness < minLikeness || likeness > maxLikeness)
			{
				notMatched++;
			}
		}
		percentage = 100 / wordsSize * notMatched;
		percentage = 100 - percentage;
		if (percentage >= matchPercentage)
		{
			viable.push_back(words[i]);
		}
	}

	if (viable.size() >= 1)
	{
		unsigned short index = rand() % viable.size();
		return viable[index];
	}
	else
	{
		// https://stackoverflow.com/questions/12863256/how-to-iterate-stdset#12863273
		unsigned short index = rand() % options.size();
		unsigned short count = 0;
		for (std::string f : options) {
			if (count == index) {
				return f;
			}
			count++;
		}
	}
}

/*
	Takes in a string and looks through words to see if it exists
	Returns boolean for whether the word is found or not
*/
bool WordList::containsWord(std::string word)
{
	for (unsigned int i = 0; i < words.size(); i++)
	{
		if (words[i] == word)
		{
			return true;
		}
	}
	return false;
}

/*
	Takes the secret word and the gussed word.
	Returns the number of letters which line up.
*/
int WordList::getLikness(std::string secret, std::string guess)
{
	int score = 0;

	// Loop through each character in the guessed word
	for (unsigned int i = 0; i < guess.size(); i++)
	{
		// Add to the score if the characters match
		// at the corresponding position in each word
		if (secret[i] == guess[i])
			score++;
	}
	return score;
}