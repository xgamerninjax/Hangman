#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <cctype>
#include <ctime>

enum class GuessStatus
{
	Valid,
	NotLetter,
	WrongLength,
	AlreadyGuessed,
};

class HangMan
{
public:
	HangMan();

	GuessStatus IsGuessValid(std::string);

	int  GetMaxTries() const;
	int GetCurrentTry() const;
	int GetLivesLeft() const;
	std::string GetHiddenWord() const;
	bool IsGameWon() const;
	

	bool ErrorChecks(std::string);
	void Reset();
	void Hangmen();
	void SubmitGuess();



private:
	int MyCurrentTry;
	int MyMaxTries; // Somewhere between 6-8 probably.
	int MyHits;
	std::string MyHiddenWord;
	std::string Wordbank;
};