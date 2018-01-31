# comp140-worksheetA
## Pseudocode for improved word choosing algorithm.

  	procedure getSecretWord(minLikeness, maxLikeness, matchPercentage)
	  minLikeness <- clamp 0, words[0].length
	  maxLikeness <- clamp 0, words[0].length
	  matchPercentage <- clamp 0, 100

	  viable <- []
	  for i = 0, 1, . . . ,words.size do
		  notMatched <- 0
		  for j = 0, 1, ..., words.size do
			  likeness <- getLikness(words[i], words[j])
			  if likeness < minLikeness or likeness > maxLikeness then
				  increment notMatched
			  end if
		  end for
		  percentage = 100 / words.size * notMatched
		  percentage = 100 - percentage
		  if percentage >= matchPercentage then
			  viable <- insert i
		  end if
	  end for
	  return viable not empty and viable.rand or words.rand
  	end procedure
