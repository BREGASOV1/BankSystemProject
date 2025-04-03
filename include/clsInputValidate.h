#pragma once
#include<iostream>
#include"clsDate.h"
using namespace std;

template<class Temp>
class clsInputValidate
{
public:
	static Temp ReadNumber(string message = "Please Enter a Validate Number!\n") {
		Temp Number;
		cin >> Number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits <streamsize>::max(), '\n');
			cout <<message;
			cin >> Number;
		}
		return Number;
	}
	

	
	
	static bool IsNumberBetween(Temp number,Temp  from, Temp to) {
		return(number >= from && number <= to);
	}
	
	
	
	static bool IsDateBetween(clsDate Date, clsDate FromDate, clsDate ToDate) {
		if (FromDate.IsBeforeDate(ToDate)) {
			return((Date.isAfterDate(FromDate) && Date.IsBeforeDate(ToDate)) || Date.AreEqualsDates(FromDate) || Date.AreEqualsDates(ToDate));
		}
		else
		{
			return((Date.isAfterDate(ToDate) && Date.IsBeforeDate(FromDate)) || Date.AreEqualsDates(FromDate) || Date.AreEqualsDates(ToDate));
		}
	}
	
	static bool IsValidateDate(clsDate Date) {
		return Date.isValidateDate();
	}
	
	static Temp ReadNumberBetween(Temp from, Temp to, string message = "\nPlease enter a number between the given range\n") {
	
		 Temp number = ReadNumber();
		 while (number > to || number < from) {
			 cout << message;
			 number = ReadNumber();
		 }
		 return number;
	}

	

	static string ReadString() {
		string line;
		getline(cin >> ws, line);
		return line;
	}

};

