#include "Hangman.h"

// Initialize Game
HangMan::HangMan() { Reset(); }

//Getters
int HangMan::GetMaxTries() const { return MyMaxTries; }
int HangMan::GetCurrentTry() const { return MyCurrentTry; }
int HangMan::GetLivesLeft() const { return (MyMaxTries + 1) - MyCurrentTry; }
std::string HangMan::GetHiddenWord() const { return MyHiddenWord; }

//Resets the game state, chooses hidden word.
void HangMan::Reset()
{
	//Read WordBank.txt and get a random word out of it
	//Assign that word as our hidden word each new game.
	//srand(time(NULL));
	srand(static_cast<unsigned int>(time(NULL)));
	std::vector<std::string> words;
	std::ifstream file("WordBank.txt");
	std::string line;
	while (getline(file, line)) words.push_back(line);
	std::string HiddenWord = words[rand() % words.size()];
	std::transform(HiddenWord.begin(), HiddenWord.end(), HiddenWord.begin(), ::tolower);
	MyHiddenWord = HiddenWord;

	constexpr int MaxTries = 6;
	MyMaxTries = MaxTries;

	MyCurrentTry = 1;
	MyHits = 0;

	return;
}

// Error Returns 
GuessStatus HangMan::IsGuessValid(std::string Guess)
{	
	if (Guess.length() != 1)
	{
		return GuessStatus::WrongLength;
	}
		
	else if (! (std::all_of(begin(Guess), end(Guess), std::isalpha)))
	{
		return GuessStatus::NotLetter;
	}

	else if (false) //TODO - Write alrady used function
	{
		return GuessStatus::AlreadyGuessed;
	}

	else
	{
		return GuessStatus::Valid;
	}
}

// Error Checks
bool HangMan::ErrorChecks(std::string Guess)
{
	GuessStatus Status = IsGuessValid(Guess);

	switch (Status)
	{
	case GuessStatus::WrongLength:
		std::cout << "\nPlease only enter one letter.\n" << std::endl;
		break;

	case GuessStatus::NotLetter:
		std::cout << "\nPlease only enter letters.\n" << std::endl;
		break;

	case GuessStatus::AlreadyGuessed:
		std::cout << "\nYou already guessed that letter.\n" << std::endl;
		break;

	case GuessStatus::Valid:
		return true;
	}
}

//If the player submits a valid guess, submit it
void HangMan::SubmitGuess()
{
	const int HiddenWordLength = MyHiddenWord.length();
	std::string Underscore = std::string(MyHiddenWord.size(), '_');
	std::string Guess = "";

	
	std::vector <char> LetterBank;
	
	LetterBank.push_back('a');
	LetterBank.push_back('b');
	LetterBank.push_back('c');
	LetterBank.push_back('d');
	LetterBank.push_back('e');
	LetterBank.push_back('f');
	LetterBank.push_back('g');
	LetterBank.push_back('h');
	LetterBank.push_back('i');
	LetterBank.push_back('j');
	LetterBank.push_back('k');
	LetterBank.push_back('l');
	LetterBank.push_back('m');
	LetterBank.push_back('n');
	LetterBank.push_back('o');
	LetterBank.push_back('p');
	LetterBank.push_back('q');
	LetterBank.push_back('r');
	LetterBank.push_back('s');
	LetterBank.push_back('t');
	LetterBank.push_back('u');
	LetterBank.push_back('v');
	LetterBank.push_back('w');
	LetterBank.push_back('x');
	LetterBank.push_back('w');
	LetterBank.push_back('z');

	std::vector <char> UsedBank;
	

	
	//Ask for guesses, so long as you have turns remaining
	//and game is not already won
	do
	{
		system("CLS");
		Hangmen();
		std::cout << std::endl;


		//Testing Spot 1

		std::cout << "DEBUG - Current word: " << MyHiddenWord << std::endl;

		std::cout << "DEBUG - Unused Letters: ";
		
		for (unsigned int i = 0; i < LetterBank.size(); i++)
		{
			std::cout << LetterBank[i] << " ";
		}

		std::cout << std::endl;

		std::cout << "DEBUG - Used Letters: ";
		for (unsigned int i = 0; i < UsedBank.size(); i++)
		{
			std::cout << UsedBank[i] << " ";
		}
		
		
		std::cout << std::endl;


		//end testing spot 1

		std::cout << std::endl;
		std::cout << "\nCharacters you've found: " << Underscore;
		if (GetLivesLeft() > 1)
		{
			std::cout << "\nYou have " << GetLivesLeft() << " wrong answers left.";
		}
		else if (GetLivesLeft() == 1)
		{
			std::cout << "\nYou have " << GetLivesLeft() << " wrong answer left.";
		}
		std::cout << "\nEnter your guess: ";
		std::getline(std::cin, Guess);
		std::transform(Guess.begin(), Guess.end(), Guess.begin(), ::tolower);

		//Ensure guess passes Error Checks
		if (ErrorChecks(Guess) == true)
		{
			//Cycle guess through each letter of hidden word
			bool LetterFound = false;
			for (int j = 0; j < HiddenWordLength; j++)
			{
				//If matched, reveal it on the blank line
				//don't incriment turn# (don't add body part to hangman)
				//and finally increase hit counter towards winning.
				if (MyHiddenWord[j] == Guess[0])
				{
					Underscore[j] = Guess[0];
					LetterFound = true;
				}
			}
			//if matched, tell player.
			if (LetterFound == true)
			{
				MyHits++;
				std::cout << "\nLetter '" << Guess << "' was found!" << std::endl;

				
				//Remove letter from bank, add it to used (needs work)
				for (int k = 0; k < 26; k++)
				{
					std::remove(LetterBank.begin(), LetterBank.end(), Guess[0]);
					UsedBank.push_back(Guess[0]);
				}
			}
			//if no matches, increase turn# (add body part to hangman)
			if (LetterFound == false)
			{
				MyCurrentTry++;
				std::cout << "\nNo matching letters!" << std::endl;


				//Remove letter from bank, add it to used (needs work)
				for (int k = 0; k < 26; k++)
				{
					std::remove(LetterBank.begin(), LetterBank.end(), Guess[0]);
					UsedBank.push_back(Guess[0]);
				}
			}
		}
		system("PAUSE");
	} while (IsGameWon() == false && MyCurrentTry <= MyMaxTries);

	return ;
}

//Win Condition
bool HangMan::IsGameWon() const
{
	//If hit counter is equal to hidden word length, win game.
	if (MyHits == MyHiddenWord.length()) { return true; }

	else { return false; }
}

//Art for each stage of Hangman
void HangMan::Hangmen()
{
	switch (MyCurrentTry)
	{
	case 1:
		std::cout << "   _____     " << std::endl;
		std::cout << "  |/   |     " << std::endl;
		std::cout << "  |    |     " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "__|_________ " << std::endl;
		break;

	case 2:
		std::cout << "   _____     " << std::endl;
		std::cout << "  |/   |     " << std::endl;
		std::cout << "  |    |     " << std::endl;
		std::cout << "  |    O     " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "__|_________ " << std::endl;
		break;
	
	case 3:
		std::cout << "   _____     " << std::endl;
		std::cout << "  |/   |     " << std::endl;
		std::cout << "  |    |     " << std::endl;
		std::cout << "  |    O     " << std::endl;
		std::cout << "  |    |     " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "__|_________ " << std::endl;
		break;
	
	case 4:
		std::cout << "   _____     " << std::endl;
		std::cout << "  |/   |     " << std::endl;
		std::cout << "  |    |     " << std::endl;
		std::cout << "  |    O     " << std::endl;
		std::cout << "  |   /|     " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "__|_________ " << std::endl;
		break;
	
	case 5:
		std::cout << "   _____     " << std::endl;
		std::cout << "  |/   |     " << std::endl;
		std::cout << "  |    |     " << std::endl;
		std::cout << "  |    O     " << std::endl;
		std::cout << "  |   /|\\   " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "__|_________ " << std::endl;
		break;
	
	case 6:
		std::cout << "   _____     " << std::endl;
		std::cout << "  |/   |     " << std::endl;
		std::cout << "  |    |     " << std::endl;
		std::cout << "  |    O     " << std::endl;
		std::cout << "  |   /|\\   " << std::endl;
		std::cout << "  |   /      " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "__|_________ " << std::endl;
		break;
	}

	return ;
}




