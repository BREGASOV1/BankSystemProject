#pragma once
#include<iostream>
#include "clsInputValidate.h"
#include"clsScreen.h"
#include"clsListClientsScreen.h"
#include"clsNewClientScreen.h"
#include"clsDeleteClientScreen.h"
#include"clsUpdateClientScreen.h"
#include"clsFindClientScreen.h"
#include"clsTransactionMenue.h"
#include"clsManageUsersMenue.h"
#include"clsLoginRegisterScreen.h"
#include"clsCurrencyMenu.h"
#include"Global.h"
using namespace std;
class clsMainMenue:protected clsScreen
{
private:
	enum enMainMenuAction { ListClients = 1, NewClient, DeleteClient, UpdateClient, FindClient, TransactionMenue, ManageUsers, CurrencyMenu, LoginRegister,  LoginPage };
	
	static enMainMenuAction _ReadMainMenueChoice() {
		return (enMainMenuAction)clsInputValidate<short>::ReadNumberBetween(1, 10, "\nPlease enter a number between 1 and 10\n");
	}

	static void _ListClientsScreen() {
		clsListClientsScreen::ShowClients();
	}

	static void _AddClientScreen() {
		clsNewClientScreen::ShowAddClientScreen();
	}

	static void _DeleteClientScreen() {
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _UpdateClientScreen() {
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _FindClientScreen() {
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _TransactionScreen() {
		clsTransactionMenue::TransactionMenue();
	}

	static void _ManageUsersScreen() {
		clsManageUsersMenue::ManageUsersMenue();

	}
	static void _LoginRegisterScreen() {
		
		clsLoginRegisterScreen::ShowLoginRegisterScree();

	}
	static void _CurrencyScreen() {
		clsCurrencyMenu::ShowCurrencyMenu();
	}
	static void _LoginScreen() {
		
		CurrentUser = CurrentUser.EmptyCurrentUser();
		
	}

	static void _BackToMainMenue() {
		cout << "\npress any key to go back to main menue......\n";
		system("pause>0");
		MainMenue();
	}

	static void _PerformMainMenueAction(enMainMenuAction MainMenueAction) {
		switch (MainMenueAction)
		{
		case clsMainMenue::ListClients:
			_ListClientsScreen();
			_BackToMainMenue();
			break;
		case clsMainMenue::NewClient:
			_AddClientScreen();
			_BackToMainMenue();
			break;
		case clsMainMenue::DeleteClient:
			_DeleteClientScreen();
			_BackToMainMenue();
			break;
		case clsMainMenue::UpdateClient:
			_UpdateClientScreen();
			_BackToMainMenue();
			break;
		case clsMainMenue::FindClient:
			_FindClientScreen();
			_BackToMainMenue();
			break;
		case clsMainMenue::TransactionMenue:
			_TransactionScreen();
			MainMenue();
			break;
		case clsMainMenue::ManageUsers:
			_ManageUsersScreen();
			MainMenue();
			break;
		case clsMainMenue::CurrencyMenu:
			_CurrencyScreen();
			MainMenue();
			break;
		case clsMainMenue::LoginRegister:
			_LoginRegisterScreen();
			_BackToMainMenue();
			break;
		case clsMainMenue::LoginPage:
			system("cls");
			_LoginScreen();
			break;
	
		}
	}

public:
	static void MainMenue() {
		clsScreen::_DrawScreenTilte("Main Menue Screen", "*");
		cout<<clsUtility::setw(20, " ")   << clsUtility::setw(38, "==") << "\n\n";
		cout<<clsUtility::setw(13, "  ")  << clsUtility::setw(13, "  ") << "Main Menue " << "\n\n";
		cout<<clsUtility::setw(20, " ")   << clsUtility::setw(38, "==") << "\n";
		cout<<clsUtility::setw(3, "	")<<clsUtility::setw(3, "	") << "[1] Show Client List." << "\n";
		cout<<clsUtility::setw(3, "	")<<clsUtility::setw(3, "	") << "[2] Add New Client." << "\n";
		cout<<clsUtility::setw(3, "	")<<clsUtility::setw(3, "	") << "[3] Delete Client." << "\n";
		cout<<clsUtility::setw(3, "	")<<clsUtility::setw(3, "	") << "[4] Update Client Info." << "\n";
		cout<<clsUtility::setw(3, "	")<<clsUtility::setw(3, "	") << "[5] Find Client." << "\n";
		cout<<clsUtility::setw(3, "	")<<clsUtility::setw(3, "	") << "[6] Transaction Menue." << "\n";
		cout<<clsUtility::setw(3, "	")<<clsUtility::setw(3, "	") << "[7] Manage Users." << "\n";
		cout<<clsUtility::setw(3, "	")<<clsUtility::setw(3, "	") << "[8] Currency Menu." << "\n";
		cout << clsUtility::setw(3, "	") << clsUtility::setw(3, "	") << "[9] Login Register." << "\n";
		cout << clsUtility::setw(3, "	") << clsUtility::setw(3, "	") << "[10] LogOut." << "\n";
		cout<< clsUtility::setw(20, " " )<<clsUtility::setw(38, "==") << "\n";
		cout << "\nChoose what do you want to do [1,10]:\n";

		_PerformMainMenueAction(_ReadMainMenueChoice());

	}
};

