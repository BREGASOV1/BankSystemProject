#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
using namespace std;
class clsDepositScreen:protected clsScreen
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

	static void _Deposit() {
		cout << "\nEnter the Account Number where you want to deposit:\n";
		string AccountNumber = clsInputValidate<string>::ReadString();
		if (!clsBankClient::isExistClient(AccountNumber))
		{
			cout << "\nThis account number is not exist, please enter a valid one: \n";
		
		}
		else {
			clsBankClient Client = clsBankClient::Find(AccountNumber);
			cout << "\nAccount was found\n";
			_Print(Client);
			cout << "\nHow much do you want to deposit?\n";
			double DepositValue = clsInputValidate<double>::ReadNumber();
			cout << "\nAre you sure you want to deposite " << DepositValue << " in \"" << Client.GetFullName() << "\" Account? Y/N\n";
			char answer;
			cin >> answer;
			if (tolower(answer) == 'y') {
				Client.Deposit(DepositValue);
				clsBankClient::enSaveResult SaveResult = Client.Save();
				switch (SaveResult)
				{
				case clsBankClient::svSavedSuccessfully:
					cout << "\nDeposit has been done successfully.\nNew Balance is: " << Client.Balance;
					break;
				case clsBankClient::svFailedEmptyObject:
					cout << "\nDepsit has not been done successfully, this is empty client account\n";
					break;
				case clsBankClient::svFailedAccountNumber:
					cout << "\nDepsit has not been done successfully, this Account number is not exist\n";
					break;

				}
			}
			else
				cout << "\nOperation was cancelled....\n";

		}
	}

public:
	static void ShowDepositScreen() {
		char repeat;
		do{
		_DrawScreenTilte("Deposit Screen", "*");
		cout << "\n\n-------------------------------------------------\n\n";
		_Deposit();
		cout << "\nDo you want to perform another deposit? Y/N\n";
		cin >> repeat;
	}while (tolower(repeat) == 'y');
	}
};

