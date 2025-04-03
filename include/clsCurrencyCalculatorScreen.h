#pragma once
#include<iostream>
#include"clsInputValidate.h"
#include"clsScreen.h"
#include"clsCurrency.h"
using namespace std;
class clsCurrencyCalculatorScreen:protected clsScreen
{
private:

	static void _Print(clsCurrency Currency) {
		cout << clsUtility::setw(10, "__");
		cout << "\nCurrency Card: \n";
		cout << "\nCountry Name:    " << Currency.GetCountryName();
		cout << "\nCurrency Code:   " << Currency.GetCurrencyCode();
		cout << "\nCurrency Name:   " << Currency.GetCurrencyName();
		cout << "\nCurrency Rate:   " << Currency.GetCurrencyRate() << "\n";
		cout << clsUtility::setw(10, "__") << endl;

	}

public:
	static void ShowCalculateCurrencyScreen() {
	
			char repeat;
			do {
				_DrawScreenTilte("Calculate Currency", "*");
				cout << "\nEnter the amount you want to calculate, the Currency Code you want to calculate from\nand the Currency Code you want to calculate to: \n";
				cout << "\nAmount:  ";
				float amount = clsInputValidate<float>::ReadNumber();
				cout << "\nFrom Currency Code: ";
				string FromCurrencyCode = clsInputValidate<string>::ReadString();
				cout << "\nTo Currency Code:   ";
				string ToCurrencyCode = clsInputValidate<string>::ReadString();
				if (clsCurrency::isExistCurrency(ToCurrencyCode) && clsCurrency::isExistCurrency(FromCurrencyCode)) {
					clsCurrency FromCurrency = clsCurrency::FindWithCurrencyCode(FromCurrencyCode);
					clsCurrency ToCurrency = clsCurrency::FindWithCurrencyCode(ToCurrencyCode);
					cout << "\n\nCalculating [" << amount << "] of " << FromCurrencyCode << " to  " << ToCurrencyCode << endl;
					_Print(FromCurrency);
					if (clsCurrency::isCurrencyCodeUSD(ToCurrencyCode)) {
						cout << "\n[" << amount << "] of " << FromCurrencyCode << " is " << FromCurrency.CalculateCurrencyToUSD(amount) << " USD \n";

					}
					else {
						cout << "\n[" << amount << "] of " << FromCurrencyCode << " is " << FromCurrency.CalculateCurrencyToUSD(amount) << " USD \n";
						cout << "\nNow for " << ToCurrencyCode << endl;
						_Print(ToCurrency);
						cout << "\n[" << amount << "] of " << FromCurrencyCode << " is " << FromCurrency.CalculateCurrencyTo(ToCurrency, amount) << "  " << ToCurrency.GetCurrencyCode() << endl;
					}
				}
				else {
					cout << "\n One or both of the Currency Codes you entered is not exist....!!\n";
				}
				cout << "\nDo you want to calculate another currency amount? Y/N\n";

				cin >> repeat;
			} while (tolower(repeat) == 'y');
		}
		
	
};

