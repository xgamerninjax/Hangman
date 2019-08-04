#include "Hangman.h"

HangMan HMGame;

void Intro();
void PlayGame();
bool PlayAgain();
void Summary();

// Entry point to the game.
int main()
{
	bool Continue = false;

	do
	{
		system("CLS");
		Intro();
		system("PAUSE");
		PlayGame();
		Continue = PlayAgain();
	} 
	while (Continue);

	return 0; // exit the game
}

// Introduction to the game.
void Intro()
{


	std::cout << "                                                    |\\|" << std::endl;
	std::cout << " _                                                  |\\|" << std::endl;
	std::cout << "| |                                                 |\\|" << std::endl;
	std::cout << "| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __       |\\|" << std::endl;
	std::cout << "| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\      |_|" << std::endl;
	std::cout << "| | | | (_| | | | | (_| | | | | | | (_| | | | |    (___)" << std::endl;
	std::cout << "|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|    (___)" << std::endl;
	std::cout << "                    __/ |                          (___)" << std::endl;
	std::cout << "                   |___/                           (___)" << std::endl;
	std::cout << "                                                  (/   \\)," << std::endl;
	std::cout << "                                                ('/     \\')" << std::endl;
	std::cout << "                                               ('/       \\')" << std::endl;
	std::cout << "                                               |/|       |/|" << std::endl;
	std::cout << "                                               |/|       |/|" << std::endl;
	std::cout << "Welcome to Hangman!                            |/|       |/|" << std::endl;
	std::cout << "                                               (-\\       /-)" << std::endl;
	std::cout << "Do you have what it takes                       \\-\\     /-/" << std::endl;
	std::cout << "to guess the word before                         \\-\\___/-/" << std::endl;
	std::cout << "you run out of turns?                             \\-----/" << std::endl;

	std::cout << std::endl;
	return;
}

// Main game functions.
void PlayGame()
{
	HMGame.Reset();
	HMGame.SubmitGuess();
	system("CLS");
	Summary();
	system("PAUSE");

	return;
}

// Ask player if they want to play again.
bool PlayAgain()
{
	for (int ResponseNum = 0; ResponseNum == 0;)
	{
		system("CLS");
		std::string Response = "";
		std::cout << "Would you like to play again? (Yes/No)" << std::endl;
		std::cout << "Response: ";
		std::getline(std::cin, Response);

		if ((Response[0] == 'y') || (Response[0] == 'Y'))
		{
			ResponseNum = 1;
			return 1;
		}
		else if ((Response[0] == 'n') || (Response[0] == 'N'))
		{
			ResponseNum = 1;
			return 0;
		}
		else
		{
			std::cout << "\nPlease enter yes or no." << std::endl;
			system("PAUSE");
		}
	}
}

//Summary of game outcome.
void Summary()
{
	if (HMGame.IsGameWon() == 1)
	{
		std::cout << "Congratulations, you've won with " << HMGame.GetLivesLeft() << " wrong answers left!" << std::endl;
	}
	else
	{
		std::cout << "   _____     " << std::endl;
		std::cout << "  |/   |     " << std::endl;
		std::cout << "  |    |     " << std::endl;
		std::cout << "  |    O     " << std::endl;
		std::cout << "  |   /|\\   " << std::endl;
		std::cout << "  |   / \\   " << std::endl;
		std::cout << "  |          " << std::endl;
		std::cout << "__|_________ " << std::endl;
		std::cout << std::endl;
		std::cout << "Better luck next time!" << std::endl;
		std::cout << "Your word was: " << HMGame.GetHiddenWord() << std::endl;
		std::cout << std::endl;
	}
}