#pragma once
#include<iostream>
#include"clsInputValidate.h"
#include"clsScreen.h"
#include"clsCurrency.h"
using namespace std;
class clsListCurrenciesScreen:protected clsScreen
{

private:

	static void _Print(clsCurrency Currency) {
		cout << left;
		cout << "| " << setw(30) << Currency.GetCountryName();
		cout << "| " << setw(17) << Currency.GetCurrencyCode();
		cout << "| " << setw(30) << Currency.GetCountryName();
		cout << "| " << setw(15) << Currency.GetCurrencyRate() << endl;
	}
public:

	static void ShowAllCurrenciesScreen() {

		vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string subTitle = "[" + to_string(vCurrencies.size()) + "] Currency(ies)";
		_DrawScreenTilte("Currencies List", "*", subTitle);
		if (vCurrencies.size() == 0)
			cout << "\n\n\n\t\t\t\tThere is no Currencies data found.....!!\n";
		else {
			cout << clsUtility::setw(58, "__") << "\n\n\n";
			cout << "| " << left<<setw(30) << "CountryName";
			cout << "| " << setw(17) << "CurrencyCode";
			cout << "| " << setw(30) << "CurrencyName";
			cout << "| " << setw(15) << "CurrencyRate" << endl;
			cout << clsUtility::setw(58, "__") << "\n\n";
			for (clsCurrency& currency : vCurrencies)
				_Print(currency);
		}
		cout << clsUtility::setw(58, "__") << endl;
	}
};

