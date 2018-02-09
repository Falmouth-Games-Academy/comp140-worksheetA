# comp140-worksheetA

string getLikeWord(string secret, int likeness, int findAttempts)  
{
	for (int i = 0 -> findAttempts)  
	{  
		int index = random(0,words.size)  
		int likenessCounter = 0  
		for (int j = 0 -> likeness)  
		{  
			if (words[index].find(secret[random(0,secret.length()]))  
			{  
				likenessCounter++  
			}  
		}  
		if (likenessCounter == likeness)  
		{  
			return words[index]  
		}  
	}  
	return getRandomWord()  
}  
