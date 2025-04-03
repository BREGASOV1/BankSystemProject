#pragma once
#include<iostream>
#include"clsInputValidate.h"
#include"clsScreen.h"
#include"clsListCurrenciesScreen.h"
#include"clsFindCurrencyScreen.h"
#include"clsUpdateCurrencyRateScreen.h"
#include"clsCurrencyCalculatorScreen.h"
using namespace std;
class clsCurrencyMenu : protected clsScreen
{
private:
	enum enCurrencyMenuOptions{ ListCurrencies = 1, FindCurrency, UpdateRate, CurrencyCalculator, MainMenu };
	 
	static enCurrencyMenuOptions _ReadCurrencyMenuOption() {
		return (enCurrencyMenuOptions)clsInputValidate<short>::ReadNumberBetween(1, 5, "\nPlease Enter a validate number between 1 and 5\n");
	}

	static void _BackToCurrencyMenu() {
		cout << "\nPress any key to go back to Currency Menu........\n";
		system("pause > 0");
		ShowCurrencyMenu();
	}
	static void _ListCurrencies() {
		clsListCurrenciesScreen::ShowAllCurrenciesScreen();
	}

	static void _FindCurrency() {
		clsFindCurrencyScreen::_ShowFindCurrencyScreen();
	}

	static void _UpdateRate() {
		clsUpdateCurrencyRateScreen::ShowUpdateRateScreen();
	}

	static void _CurrencyCalculator() {
		clsCurrencyCalculatorScreen::ShowCalculateCurrencyScreen();
	}

	static void _PerformCurrencyMenuOption(enCurrencyMenuOptions CurrencyOption) {
		switch (CurrencyOption)
		{
		case clsCurrencyMenu::ListCurrencies:
			_ListCurrencies();
			_BackToCurrencyMenu();
			break;
		case clsCurrencyMenu::FindCurrency:
			_FindCurrency();
			_BackToCurrencyMenu();
			break;
		case clsCurrencyMenu::UpdateRate:
			_UpdateRate();
			_BackToCurrencyMenu();
			break;
		case clsCurrencyMenu::CurrencyCalculator:
			_CurrencyCalculator();
			_BackToCurrencyMenu();
			break;
		case clsCurrencyMenu::MainMenu:
			break;
		
		}
	}

public:
	static void ShowCurrencyMenu() {
		if (!clsScreen::AccessPermission(clsUser::pCurrency)) {
			cout << "\nPress any key to go back to main menue......\n";
			system("pause > 0");
			return;
		}
		_DrawScreenTilte("Currency Menu", "*");
		cout << clsUtility::setw(20, " ") << clsUtility::setw(38, "==") << "\n\n";
		cout << clsUtility::setw(13, "  ") << clsUtility::setw(13, "  ") << "Currency Menu Screen" << "\n\n";
		cout << clsUtility::setw(20, " ") << clsUtility::setw(38, "==") << "\n";
		cout << clsUtility::setw(3, "	") << clsUtility::setw(3, "	") << "[1] List Currencies." << "\n";
		cout << clsUtility::setw(3, "	") << clsUtility::setw(3, "	") << "[2] Find Currency." << "\n";
		cout << clsUtility::setw(3, "	") << clsUtility::setw(3, "	") << "[3] Update Currency Rate." << "\n";
		cout << clsUtility::setw(3, "	") << clsUtility::setw(3, "	") << "[4] Currency Calculator." << "\n";
		cout << clsUtility::setw(3, "	") << clsUtility::setw(3, "	") << "[5] Main Menu." << "\n";
		cout << clsUtility::setw(20, " ") << clsUtility::setw(38, "==") << "\n";
		cout << "\nChoose what do you want to do [1,5]:\n";
		_PerformCurrencyMenuOption(_ReadCurrencyMenuOption());
	}
};


