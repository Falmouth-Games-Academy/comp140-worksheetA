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

std::string WordList::getRandomWord()
{
	int index = rand() % words.size();
	return words[index];
}

/*
	Clamps the value between the minimum and maximum
*/
int clamp(double value, double min, double max) {
	return (unsigned int)fmin(max, fmax(value, min));
}

/*
	Returns a random word which has been chosen based on its likeness score to its fellow words
*/
std::string WordList::getSecretWord(const std::set<std::string> &options, unsigned int minLikeness = 2, unsigned int maxLikeness = 6, unsigned int matchPercentage = 10)
{
	// Get the first word to base the length off of
	auto it = options.begin();
	std::string baseWord = *it;

	// Clamp the values to keep them within range
	minLikeness = clamp(minLikeness, 0, baseWord.size());
	maxLikeness = clamp(minLikeness, 0, baseWord.size());
	matchPercentage = clamp(matchPercentage, 0, 100);
	
	// Use a vector to store words which fit the requested requirements
	std::vector<std::string> viable;

	// Initalise variables to be used in the for loop
	int notMatched, likeness, percentage = 0;
	int wordsSize = options.size();

	for (std::string word1 : options)
	{
		notMatched = 0;
		// Compare the likeness score of word1 to all other words
		for (std::string word2 : options)
		{
			// Get the likeness score of word1 to word2
			likeness = getLikness(word1, word2);

			// Make word1 more likely to be excluded from viable words if the
			// likeness score is below or above the minimum or maximum bounds
			if (likeness < minLikeness || likeness > maxLikeness)
			{
				notMatched++;
			}
		}

		// Workout the percentage word1 matches the minimum and manimum bounds
		percentage = 100 / wordsSize * notMatched;
		percentage = 100 - percentage;

		// Add the word to the viable list if it meets the likeness requirement
		if (percentage >= matchPercentage)
		{
			viable.push_back(word1);
		}
	}

	// If there's at least one word in the viable list
	if (viable.size() >= 1)
	{
		// Pick a random position in the set and return the secret word
		unsigned short index = rand() % viable.size();
		return viable[index];
	}
	else
	{
		// Otherwise resort back to the options set and pick a secret word from that
		// https://stackoverflow.com/questions/20477545/element-at-index-in-a-stdset
		unsigned short index = rand() % options.size();
		auto it = options.begin();
		std::advance(it, index);
		return *it;
	}
}

/*
	Takes in a string and looks through words to see if it exists
	Returns boolean for whether the word is found or not
*/
bool WordList::containsWord(const std::set<std::string> &options, std::string &word)
{
	auto search = options.find(word);

	// The search will return a number one longer than the string (optiosn.end()) if not found
	return search != options.end();
}

/*
	Takes the secret word and the gussed word.
	Returns the number of letters which line up.
*/
int WordList::getLikness(std::string &secret, std::string &guess)
{
	int score = 0;

	// Loop through each character in the guessed word
	for (unsigned int i = 0; i < secret.size(); i++)
	{
		// Add to the score if the characters match
		// at the corresponding position in each word
		if (secret[i] == guess[i])
			score++;
	}
	return score;
}