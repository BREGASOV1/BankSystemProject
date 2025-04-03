#pragma once
#include<iostream>
#include<vector>
using namespace std;
class clsString
{

private:

	string _Value;

protected:

	static bool isVowel(char Character) {
		Character = tolower(Character);
		return(Character == 'a' || Character == 'e' || Character == 'u' || Character == 'i' || Character == 'o');
	}
	
	static char InvertCharCase(char TheCharacter) {
		return isupper(TheCharacter) ? tolower(TheCharacter) : toupper(TheCharacter);

	}

public:
	clsString() {
		_Value = "";
	}

	clsString(string value) {
		_Value = value;
	}

	void setValue(string Value) {
		_Value = Value;

	}

	string getValue() {
		return _Value;
	}

	__declspec(property(get = getValue, put = setValue))string Value;

	static short Length(string text) {
		return text.length();
	}
	short Length() {
		return Length(_Value);
	}

	static short CountSpecificChar(string text, char WantedChar, bool Case = true) {
		short counter = 0;
		for (short i = 0; i < text.length(); i++)
		{
			if (Case) {
				if (text[i] == WantedChar)
					counter++;
			}
			else {
				if (tolower(text[i]) == tolower(WantedChar))
					counter++;
			}
		}
		return counter;
	}
	short CountSpecificChar(char WantedChar, bool Case = true) {
		return CountSpecificChar(_Value, WantedChar, Case);
	}

	static short CountLowerCaseLetters(string text) {
		short counter = 0;
		for (short i = 0; i < text.length(); i++)
		{
			if (islower(text[i]))
				counter++;

		}
		return counter;

	}
	short CountLowerCaseLetters() {
		return 	CountLowerCaseLetters(_Value);
	}

	static short CountCapitalLetters(string text) {
		short counter = 0;
		for (short i = 0; i < text.length(); i++)
		{
			if (isupper(text[i]))
				counter++;

		}
		return counter;
	}
	short CountCapitalLetters() {
		return CountCapitalLetters(_Value);
	}

	static short CountVowels(string text) {
		short counter = 0;
		for (int i = 0; i < text.length(); i++)
		{
			if (isVowel(text[i]))
				counter++;
		}
		return counter;
	}
	short CountVowels() {
		return  CountVowels(_Value);
	}
	
	static short CountEachWordInString(string text) {
		short counter = 0;
		string word = "";
		string delim = " ";
		short pos = 0;
		while ((pos = text.find(delim)) != std::string::npos) {
			if ((word = text.substr(0, pos)) != "")
				counter++;
			text = text.erase(0, pos + delim.length());
		}
		if (text != "")
			counter++;
		return counter;
	}
	short CountEachWordInString() {
		return CountEachWordInString(_Value);
	}

	static string UpperFirstLetter(string name) {
		bool isFirstLetter = true;
		for (int i = 0; i < name.length(); i++)
		{
			if (name[i] != ' ' && isFirstLetter)
				name[i] = toupper(name[i]);
			isFirstLetter = (name[i] == ' ' ? true : false);

		}
		return name;
	}
	string UpperFirstLetter() {
		return UpperFirstLetter(_Value);
	}

	static string LowerFirstLetter(string name) {
		bool isFirstLetter = true;
		for (int i = 0; i < name.length(); i++)
		{
			if (name[i] != ' ' && isFirstLetter)
				name[i] = tolower(name[i]);
			isFirstLetter = (name[i] == ' ' ? true : false);

		}
		return name;
	}
	string LowerFirstLetter() {
		return 	LowerFirstLetter(_Value);
	}

	static string LowerOrUpperString(char LetterCase, string name) {
		if (isupper(LetterCase) == 'L') {
			for (int i = 0; i < name.length(); i++)
			{
				if (name[i] != ' ')
					name[i] = tolower(name[i]);
			}
		}
		else {
			for (int i = 0; i < name.length(); i++)
			{
				if (name[i] != ' ')
					name[i] = toupper(name[i]);
			}

		}
		return name;
	}
	string LowerOrUpperString(char LetterCase) {
		return LowerOrUpperString(LetterCase, _Value);
	}

	static string InvertStringCase(string text) {
		for (short i = 0; i < text.length(); i++)
		{
			text[i] = InvertCharCase(text[i]);

		}
		return text;
	}
	string InvertStringCase() {
		return InvertStringCase(_Value);
	}

	static void PrintFirstLetterOfEachWord(string name) {
		bool isFirstLetter = true;
		for (int i = 0; i < name.length(); i++)
		{
			if (name[i] != ' ' && isFirstLetter)
				cout << name[i] << " ";
			isFirstLetter = (name[i] == ' ' ? true : false);

		}
	}
	void PrintFirstLetterOfEachWord() {
		return PrintFirstLetterOfEachWord(_Value);
	}

	static void PrintEachWordInString(string text) {
		string word = "";
		string delim = " ";
		short pos = 0;
		while ((pos = text.find(delim)) != std::string::npos) {
			word = text.substr(0, pos + delim.length());
			if (word != " ")
				cout << word << endl;
			text = text.erase(0, pos + delim.length());
		}
		if (text != " ")
			cout << text << endl;
	}
	void PrintEachWordInString() {
		PrintEachWordInString(_Value);
	}

	static void PrintVowelsInString(string text) {
		cout << endl;
		for (short i = 0; i < text.length(); i++)
		{

			if (isVowel(text[i]))
				cout << text[i] << "	";

		}
	}
	void PrintVowelsInString() {
		PrintVowelsInString(_Value);
	}

	static vector<string> SplitString(string text, string delim) {
		vector<string> vWords;
		string* Word = new string;
		short* pos = new short;
		while ((*pos = text.find(delim)) != std::string::npos)
		{
			*Word = text.substr(0, *pos);
			if (*Word != "")
				vWords.push_back(*Word);
			text = text.erase(0, *pos + delim.length());


		}
		if (text != "")
			vWords.push_back(text);
		delete Word, pos;
		return vWords;

	}
	vector<string> SplitString(string delim) {
		return SplitString(_Value, delim);
	}

	static string TrimLeft(string text) {

		for (short i = 0; i < text.length(); i++)
		{
			if (text[i] != ' ')
			{
				text = text.erase(0, i);
				break;
			}
		}
		return text;
	}
	string TrimLeft() {
		return TrimLeft(_Value);
	}

	static string TrimRight(string text) {

		for (short i = text.length() - 1; i >= 0; i--)
		{
			if (text[i] != ' ')
			{
				text = text.erase(i, text.length() - 1);
				break;
			}
		}
		return text;
	}
	string TrimRight() {
		return TrimRight(_Value);

	}

	static string Trim(string text) {

		return (TrimLeft(TrimRight(text)));
	}
	string Trim() {
		return Trim(_Value);
	}

	static string JoinString(vector<string> vWords, string SpecialSeprator = " ") {
		string Phrase = "";
		for (string& word : vWords)
		{
			Phrase += word;
			Phrase += SpecialSeprator;
		}
		return Phrase.substr(0, Phrase.length() - SpecialSeprator.length());
	}
	static string JoinString(string arrWords[], int length, string SpecialSeprator) {
		string Phrase = "";
		for (int i = 0; i < length; i++)
		{
			Phrase += arrWords[i];
			if (i == length - 1)
				continue;
			Phrase += SpecialSeprator;
		}
		return Phrase;
	}

	static string ReverseString(string text) {
		string NewText = "";
		vector<string> vNewText = SplitString(text, " ");
		vector<string>::iterator iter = vNewText.end();
		while (iter != vNewText.begin())
		{

			--iter;
			NewText += *iter + " ";


		}

		return NewText.substr(0, NewText.length() - 1);
	}
	string ReverseString() {
		return ReverseString(_Value);
	}

	static string ReplaceWordsInStringCaseSensitive(string text, string OldWord, string NewWord) {
		short pos = 0;
		while ((pos = text.find(OldWord)) != std::string::npos)
		{
			text.replace(pos, OldWord.length(), NewWord);



		}
		return text;
	}
	string ReplaceWordsInStringCaseSensitive(string OldWord, string NewWord) {
		return ReplaceWordsInStringCaseSensitive(_Value, OldWord, NewWord);
	}

	static string ReplaceWordsInStringOptimization(string text, string OldWord, string NewWord,string delim, bool Case) {
		vector<string> vText = SplitString(text, delim);
		if (Case) {
			for (string& word : vText) {
				if (word == OldWord)
					word = NewWord;
			}
		}
		else {
			for (string& word : vText) {
				if (LowerOrUpperString('L', word) == LowerOrUpperString('L', OldWord))
					word = NewWord;
			}
		}
		return JoinString(vText);
	}
	string ReplaceWordsInStringOptimization(string OldWord, string NewWord,string delim, bool Case) {
		return ReplaceWordsInStringOptimization(_Value, OldWord, NewWord,delim, Case);
	}

	static string RemovePunctuationsFromString(string text) {
		//string newText = " ";
		for (int i = 0; i < text.length(); i++)
		{
			/*if(!ispunct(text[i]))
			newText += text[i]*/
			if (ispunct(text[i]))
				text.erase(i, 1);
		}
		return text;
	}
	string RemovePunctuationsFromString() {
		return RemovePunctuationsFromString(_Value);
	}

};


	

