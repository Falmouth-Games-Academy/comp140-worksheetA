# comp140-worksheetA

Pseudocode for improved word picker:
	get secretWord;
	options.insert(secretWord)
	while (optionsList < numberOfWords)
	{
		word = RandomWord;
		likeness = getLikeness(secretWord, randomWord);
		if (likeness >= 1)
			options.insert(randomWord);
		else
			continue;
	}
