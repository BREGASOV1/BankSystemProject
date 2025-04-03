#pragma once
#include<iostream>
#include"clsInputValidate.h"
#include"clsScreen.h"
#include"clsCurrency.h"
using namespace std;
class clsFindCurrencyScreen:protected clsScreen

{
private:
	static void _Print(clsCurrency Currency) {
		cout << clsUtility::setw(10, "__");
		cout << "\nCurrency Card: \n";
		cout << "\nCountry Name:    " << Currency.GetCountryName();
		cout << "\nCurrency Code:    " << Currency.GetCurrencyCode();
		cout << "\nCurrency Name:   " << Currency.GetCurrencyName();
		cout << "\nCurrency Rate:   " << Currency.GetCurrencyRate()<<"\n";
		cout << clsUtility::setw(10, "__") << endl;

	}

	static void _FindCurrency() {
		char repeat;
		do {
			cout << "\nDo you want to search using [1] Currency Code OR [2] Country Name?\n";
			short answer = clsInputValidate<short>::ReadNumberBetween(1, 2, "\nPlease choose either 1 or 2\n");
			if (answer == 1) {
				cout << "\nEnter the Currency Code:  ";
				string CurrencyCode = clsInputValidate<string>::ReadString();

				clsCurrency Currency = Currency.FindWithCurrencyCode(CurrencyCode);
				if (Currency.isEmpty())
					cout << "\nthere is no currency exist with this Currency Code\n";
				else
					_Print(Currency);
			}
			else {
				cout << "\nEnter the country name:  ";
				string CountryName = clsInputValidate<string>::ReadString();
				clsCurrency Currency = Currency.FindWithCountryName(CountryName);
				if (Currency.isEmpty())
					cout << "\nthere is no currency exist with this Country Name\n";
				else
					_Print(Currency);
			}
			cout << "\nDo you want to search again? Y/N \n";
			cin >> repeat;
		} while (tolower(repeat) == 'y');
	}

public:
	static void _ShowFindCurrencyScreen() {
		_DrawScreenTilte("Find Currency Screen", "*");
		_FindCurrency();
	}
};

