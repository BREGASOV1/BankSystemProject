#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
using namespace std;
class clsFindClientScreen:protected clsScreen
{
private:

	
	static void _Print(clsBankClient Client) {
		cout << "\n\n--------------------------------------\n";
		cout << "Client Card: \n";
		cout << left << setw(15) << "\nFirts Name: " << Client.FirstName;
		cout << left << setw(15) << "\nLast Name: " << Client.LastName;
		cout << left << setw(15) << "\nEmail: " << Client.Email;
		cout << left << setw(15) << "\nPhone: " << Client.PIN;
		cout << left << setw(15) << "\nAccount NO: " << Client.GetAccountNumber();
		cout << left << setw(15) << "\nPIN: " << Client.PIN;
		cout << left << setw(15) << "\nBalance: " << to_string(Client.Balance);
		cout << "\n--------------------------------------\n";
	}

	static void _Find() {
		char answer;
		cout << "\nEnter the account number of the Client you want to find:\n";
		string AccountNumber = clsInputValidate<string>::ReadString();
		if (!clsBankClient::isExistClient(AccountNumber)) {
			cout << "\nThe account number you entered was not found.";
			
		}
		else {
			clsBankClient Client = clsBankClient::Find(AccountNumber);
			cout << "\nThe Client who has the Account Number [" << AccountNumber << "] was found\n";
			_Print(Client);
		}
	}

public:

	static void ShowFindClientScreen() {
		if (!clsScreen::AccessPermission(clsUser::pFindClient)) {
			return;
		}
		char repeat;
		do {
			clsScreen::_DrawScreenTilte("Find Client Screen", "*");
			cout << "\n\n-------------------------------------------------\n\n";
			_Find();
			cout << "\nDo you want to search another account? Y/N\n";
			cin >> repeat;
		} while (tolower(repeat) == 'y');
	}
};

