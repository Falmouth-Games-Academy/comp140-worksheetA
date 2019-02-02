#include "stdafx.h"
#include "TerminalGame.h"

FTerminalGame game; // Initialize game

int main()
{
	PrintIntro();

	do
	{
		game.difficulty = game.ChooseDifficulty();
		SetupGame();
		PlayGame();
		PrintPostGameFeedback();
	} 
	while (bAskToPlayAgain());
	
	return 0;
}

// Prompts the player to increase the size of their cmd.exe window for optimal player experience
void PrintIntro()
{
	std::cout << "				PLEASE INCREASE THE WIDTH OF THE \
GAME WINDOW UNTIL THIS LINE FITS ON ONE LINE			" << std::endl;
	std::cout << "----------------------------------------------------------------------\
----------------------------------------------------------------------" << std::endl;
}

void SetupGame()
{
	game.Reset( game.difficulty ); // Reset the game based on the player's chosen difficulty

	/// This creates a new instance of the FWordList class
	// A list of appropriate possible words for the current word length
	FWordList wordList( game.GetWordLength() );

	AddSecretWord(wordList);
	AddDummyWords(wordList);
}

void AddSecretWord(FWordList wordList)
{
	// Choose secret word
	game.secretWord = wordList.chooseRandomWord();

	// Put the secret word in the set
	game.activeWords.insert(game.secretWord);

	// Display secret word at the top of the screen
	std::cout << game.secretWord << std::endl << std::endl;
}

void AddDummyWords(FWordList wordList)
{
	// Fill the set with other random words
	while (game.activeWords.size() < game.GetNumberOfWords())
	{
		std::string word = wordList.chooseRandomWord();
		game.activeWords.insert(word);
	}
}

void PlayGame()
{
	int likeness = -1;

	do 
	{
		PrintGameScreen(likeness);
		GetPlayerGuess();
		CheckGuess();
		likeness = HandleGuess();
	}
	while (game.livesLeft > 0);
}

void PrintGameScreen(int likeness)
{
	// Display all words
	for each (std::string word in game.activeWords)
	{
		std::cout << word << std::endl;

		// Sleep for 50 milliseconds before printing the next word
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	std::cout << game.playerInput << game.messageToPlayer << std::endl;

	// if likeness >= 0
		// print likeness on the end of the messageToPlayer

	// TODO add a new message for each bracket combo or valid guess, don't add a new message for each invalid guess
		// This could be accomplished by incrementing a 'line number' integer every new line
		// then having a set of previous valid messages which we add to from the bottom, pushing old ones up
		// we would have to fill it with empty space but, it could work
}

void GetPlayerGuess()
{
	std::cout << "Your guess: ";

	std::getline(std::cin, game.playerInput);
}

// Checks if the guess is in the list of words (or in the list of bracket combos) and capitalizes it.
void CheckGuess()
{
	// Check if the player's guess starts with an open bracket and ends with a closed bracket
	
	if (bGuessStartsWithBrackets() && bGuessEndsWithBrackets())
	{
		// TODO brackets and stuff

		game.guessStatus = EGuessStatus::Bad_Brackets;
		return;
	}

	// if playerGuess starts with a bracket
		// if playerGuess in the list of valid bracket combos
			// game.guessStatus = EGuessStatus::Good_Brackets;
		// else 
			// game.guessStatus = EGuessStatus::Bad_Brackets;
		// return;
	
	std::string caps = "";
	for (auto c : game.playerInput)
	{
		if ( ! isalpha( c )) // Reject guess if any non-alphabet characters found
		{
			game.guessStatus = EGuessStatus::Invalid;
			return;
		}

		c = toupper( c );
		caps = caps + c;
	}
	// Turn the player's input into capital letters
	game.playerInput = caps;

	if ( game.playerInput == game.secretWord )
	{
		game.guessStatus = EGuessStatus::Winner;
		return;
	}

	if ( game.playerInput.length() != game.GetWordLength() )
	{
		game.guessStatus = EGuessStatus::Wrong_Length;
		return;
	}

	// Simplest way of checking if a specific element is in a set or not
	if ( game.activeWords.count( game.playerInput ))
	{
		game.guessStatus = EGuessStatus::OK;
		return;
	}

	game.guessStatus = EGuessStatus::Unrecognized;
}

bool bGuessStartsWithBrackets()
{
	std::string openParentheses = "(";
	std::string openSquigglies = "{";
	std::string openBrackets = "[";
	std::string openChevrons = "<";

	if ( game.playerInput.find( openParentheses ) == 0 )
	{
		return true;
	}
	else if ( game.playerInput.find( openSquigglies ) == 0 )
	{
		return true;
	}
	else if ( game.playerInput.find( openBrackets ) == 0 )
	{
		return true;
	}
	else if ( game.playerInput.find( openChevrons ) == 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool bGuessEndsWithBrackets()
{
	std::string closedParentheses = ")";
	std::string closedSquigglies = "}";
	std::string closedBrackets = "]";
	std::string closedChevrons = ">";

	if ( game.playerInput.find( closedParentheses ) == ( game.playerInput.length() - 1 ))
	{
		return true;
	}
	else if ( game.playerInput.find( closedSquigglies ) == ( game.playerInput.length() - 1 ))
	{
		return true;
	}
	else if ( game.playerInput.find( closedBrackets ) == ( game.playerInput.length() - 1 ))
	{
		return true;
	}
	else if ( game.playerInput.find( closedChevrons ) == ( game.playerInput.length() - 1 ))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Returns likeness for a valid guess, returns a negative number otherwise
int HandleGuess()
{
	switch (game.guessStatus)
	{
	case EGuessStatus::OK:
		// Take a life from the player, return likeness score
		game.messageToPlayer = ": Likeness = ";
		return SubmitGuess();

	case EGuessStatus::Winner:
		// Skip guess feedback, go straight to end screen
		game.messageToPlayer = "";
		return -1;

	case EGuessStatus::Good_Brackets:
		// Take a life from the player, decide whether the brackets reset the lives or simply remove a dud
		SubmitBrackets();
		return -1;

	case EGuessStatus::Bad_Brackets:
		// Failed attempt at a bracket combo, take a life from the player anyway
		LaughAtPlayer();
		return -1;

		// Statuses below this line do not remove a life from the player

	case EGuessStatus::Wrong_Length:
		game.messageToPlayer = ": Incorrect word length. Try again.";
		return -1;

	case EGuessStatus::Invalid:
		game.messageToPlayer = ": Invalid guess. Try again.";
		return -1;

	case EGuessStatus::Unrecognized:
		game.messageToPlayer = ": That word is not present. Try again.";
		return -1;
	}
	return -1;
}

int SubmitGuess()
{
	int likeness = 0;

	// for every character in Guess, compare it to the secret word
	for (int i = 0; i < game.GetWordLength(); i++)
	{
		// if both characters in position [i] are the same
		if (toupper(game.playerInput[i]) == game.secretWord[i])
		{
			// increment (add 1 to) the likeness score
			likeness++;
		}
	}
	return likeness;
}

void SubmitBrackets()
{
	// TODO: Add bracket pairs which have a 1/4 chance to reset tries, otherwise they remove a word (not the secret word) from the screen and the set

	// To get here, the player must have submitted a valid bracket and punctuation combo
	// Roll a 4 sided dice. 

	// If don't we land a 4, 
		// we remove a random word from the list of dummy words
		// RemoveDummyWord()
			// this will basically remove a word from the list, but if it's the secret word or it starts with an open bracket, don't
		// set the player message to 'Dud Removed: [REMOVED-WORD]'

		// Add the [REMOVED-WORD] to a list of removed words?
			// Have the PrintGameScreen comb through this removed words list, replacing removed words (and bracket combos) with underscores
			// TODO keep in mind that in FALLOUT, words (but not bracket combos) wrap around to the next line (even into the second section)
				// For this reason, whatever we print will have to be completely separate from what really exists
				// We will have to just print everything one character at a time (oh if only I could delay stuff by a millisecond)

	// Otherwise
		//we'll reset the player's lives back to 4.
		// set the player message to "Tries Reset."
}

// Punish the player for failing to enter a bracket combo properly, by removing a life and laughing at them
void LaughAtPlayer()
{
	game.livesLeft--;

	std::cout << "haha" << std::endl;
}

void PrintPostGameFeedback()
{
	if (game.livesLeft > 0)
	{
		std::cout << "you the winner" << std::endl;
	}
	else
	{
		std::cout << "oof" << std::endl;
	}
}

// Uses the first letter of the player's input to determine whether they want to play another game.
bool bAskToPlayAgain()
{
	std::string playerInput = "";
	std::string FirstLetter = "default"; // FirstLetter needs to be initialized outside of the 'do' loop, any value would work here.

	do
	{
		std::cout << "Do you want to play again?" << std::endl;;
		std::getline(std::cin, playerInput);

		FirstLetter = tolower(playerInput[0]); // Changing FirstLetter to lowercase allows us to accept mixed-case "Y" and "y" as valid input
	} 
	while ((FirstLetter != "y") && (FirstLetter != "n")); // This will prompt the player to enter until they give us a Y or an N.

	return (FirstLetter == "y");  // If the player said 'yes', we return true and the game restarts. If the player said "no", the game returns false and the program closes.
}
