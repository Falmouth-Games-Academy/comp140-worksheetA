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
	words.erase(words.begin() + index);
	return words[index];
}

std::string WordList::getLikeWord(std::string secret, int likeness, int findAttempts)
{
	for (int i = 0; i < findAttempts; i++)
	{
		int index = rand() % words.size();
		int likenessCounter = 0;
		for (int j = 0; j < likeness; j++)
		{
			if (words[index].find(secret[rand()%(secret.length()-1)]) != std::string::npos)
			{
				likenessCounter++;
			}
		}
		if (likenessCounter == likeness)
		{
			return words[index];
		}
	}
	return getRandomWord();
}