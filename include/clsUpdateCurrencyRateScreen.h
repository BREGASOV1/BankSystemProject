#pragma once
#include<iostream>
#include"clsInputValidate.h"
#include"clsScreen.h"
#include"clsCurrency.h"
using namespace std;
class clsUpdateCurrencyRateScreen:protected clsScreen
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

	static void _UpdateRate() {
		char repeat;
		do
		{
			cout << "\nEnter the Currency Code you want to update its Rate: ";
			string CurrencyCode = clsInputValidate<string>::ReadString();
			if (clsCurrency::isExistCurrency(CurrencyCode)) {
				clsCurrency Currency = clsCurrency::FindWithCurrencyCode(CurrencyCode);
				_Print(Currency);
				cout << "\nEnter the new Rate: ";
				float NewRate = clsInputValidate<float>::ReadNumber();
				cout << "\nAre you sure you want to update the rate of " << CurrencyCode << " form " << Currency.GetCurrencyRate() << " to " << NewRate << " ? Y / N\n";
				char answer;
				cin >> answer;
				if (tolower(answer) == 'y') {
					if (Currency.UpdateRate(NewRate)) {
						cout << "\nCurrency Rate has been updated successfully...\n";
						_Print(Currency);
					}
					else {
						cout << "\nCurrency Rate has not been updated successfully...\n";
					}
				}
				else {
					cout << "\nOperation was Cancelled ...... \n";

				}
			}
			else {
				cout << "\nThere is no Currency with Currency Code...!!\n";
			}
			
			cout << "\nDo you want to update another Rate? Y/N\n";
			cin >> repeat;

		} while (tolower(repeat)=='y');
	}
	
public:

	static void ShowUpdateRateScreen() {
		_DrawScreenTilte("Update Currency Rate", "*");
		_UpdateRate();
	}
};

