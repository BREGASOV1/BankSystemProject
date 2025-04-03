#pragma once
#include<iostream>
#include"clsDate.h"
using namespace std;
class clsUtility
{
public:
	enum enCharType{ SmallLetter = 1, CapitalLetter, SpecialCharacter, Digit, Mix};
	static void  Srand()
	{
		//Seeds the random number generator in C++, called only once
		srand((unsigned)time(NULL));
	}
	
	static string setw(short number, string delim) {
		string line = "";
		for (short i = 1; i <= number; i++)
		{
			line += delim;

		}
		return line;
	}

	static int RandomNumberInRange(int From, int To) {
		int random;
		random = rand() % (To - From + 1) + From;
		return random;
	}
	static char GetRandomCharacter(enCharType CharType) {
		if (CharType == Mix)
		{
			//Capital/Samll/Digits only
			CharType = (enCharType)RandomNumberInRange(1, 3);

		}

		string temp = "";
		switch (CharType)
		{
		case SmallLetter:
			return char(RandomNumberInRange(97, 122));
			break;
		case CapitalLetter:
			return char(RandomNumberInRange(65, 90));
			break;
		case SpecialCharacter:
			return char(RandomNumberInRange(33, 47));
			break;
		case Digit:
			return char(RandomNumberInRange(48, 57));
			break;

		}
	}
	static string GenerateRandomWord(enCharType CharType, short length) {
		string RandomWord;

		for (int j = 0; j < length; j++)
		{
			RandomWord += GetRandomCharacter(CharType);

		}

		return RandomWord;
	}
	static string GenerateKey(enCharType CharType = CapitalLetter) {
		string RandomKey="";
		for (int i = 0; i < 4; i++)
		{
			RandomKey += GenerateRandomWord(CharType, 4);
			if (i == 3)
				continue;
			RandomKey += "-";
		}
		return RandomKey;
	}
	static void RandomKeysArray(string arr[], int arrLength) {
		for (int i = 0; i < arrLength; i++)
		{
			arr[i] = GenerateKey();
		}
	}
	static void Swap(int& A, int& B)
	{
		int Temp;

		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(double& A, double& B)
	{
		double Temp;

		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(bool& A, bool& B)
	{
		bool Temp;

		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(char& A, char& B)
	{
		char Temp;

		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(string& A, string& B)
	{
		string Temp;

		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(clsDate& A, clsDate& B)
	{
		clsDate::SwapDate(A, B);

	}
	static void ShuffledArray(int arr[100], int arrLength) {

		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumberInRange(1, arrLength) - 1], arr[RandomNumberInRange(1, arrLength) - 1]);

		}

	}
	static void ShuffleArray(string arr[100], int arrLength)
	{

		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumberInRange(1, arrLength) - 1], arr[RandomNumberInRange(1, arrLength) - 1]);
		}

	}
	static string EncryptText(string text, int EncryptionKey) {
		for (int i = 0; i <= text.length(); i++)
		{
			text[i] = char((int)text[i] + EncryptionKey);

		}
		return text;
	}
	static string DecryptText(string text, int EncryptionKey) {
		for (int i = 0; i <= text.length(); i++)
		{
			text[i] = char((int)text[i] - EncryptionKey);

		}
		return text;
	}
	static void RandomNumbersArray(int arr[100], int arrLength, int From, int To)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = RandomNumberInRange(From, To);
	}
	static void RandomWordsArray(string arr[100], int arrLength, enCharType CharType, short Wordlength)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateRandomWord(CharType, Wordlength);

	}

};

