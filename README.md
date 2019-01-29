# Comp140-WorksheetA

### Improved word choosing algorithm pseudocode

```
Procedure GetRandomWordOfLikeness( likeness, WordsList, secrateWord)

	do while GetLikeness(word, secretWord) == likeness;
		word = getRandomeWord()
	end do while
	
	return word
end procedure


randomLikeness = random 0, wordLength-1
randomWord = GetWordOfLikeness(randomLikeness, wordsList, secretWord);

insert randomWord into options;
```