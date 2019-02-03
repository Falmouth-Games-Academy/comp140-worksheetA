#HOW TO USE
Open main.cpp and run it.

#IMPROVED WORD CHOOSING ALGORITHM
'''
new integer array variable = [no of words with likelines 0, 1 ,2 ,3] 
	//must add up to total number of words
	//may be higher/lower for different game difficulty that I have implemented
while size of list of words is smaller than number of words
	get random word from words vector of the same length as secret word
	check random word's likeliness to secret word
	if word's likeliness exists in an array variable and an array variable at the likleliness level is bigger than 0
		add word to set of words
		remove one from an array variable at the likleliness level
	end if
end while loop
'''
