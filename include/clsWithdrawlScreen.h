#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
using namespace std;
class clsWithdrawlScreen:clsScreen
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
		cout << left << setw(15) << "\nBalance: " << Client.Balance;
		cout << "\n--------------------------------------\n";
	}

	static void _Withdrawl() {
		char repeat = 'y';
		cout << "\nEnter the Account Number where you want to withdrawl from :\n";
		string AccountNumber = clsInputValidate<string>::ReadString();
		if (clsBankClient::isExistClient(AccountNumber)) {
			clsBankClient Client = clsBankClient::Find(AccountNumber);
			cout << "\nAccount was found\n";
			_Print(Client);
			do {
				cout << "\nHow much do you want to withdrawl?\n";
				double WithdrawlValue = clsInputValidate<double>::ReadNumber();
				if (WithdrawlValue <= Client.Balance) {
					cout << "\nAre you sure you want to withdrawl " << WithdrawlValue << " from \"" << Client.GetFullName() << "\" Account? Y/N\n";
					char answer;
					cin >> answer;
					if (tolower(answer) == 'y') {
						if (Client.Withdrawl(WithdrawlValue)) {
							clsBankClient::enSaveResult SaveResult = Client.Save();
							switch (SaveResult)
							{
							case clsBankClient::svSavedSuccessfully:
								cout << "\nWithdrawl has been done successfully.\nNew Balance is: " << Client.Balance;
								repeat = 'n';
								break;
							case clsBankClient::svFailedEmptyObject:
								cout << "\nWithdrawl has not been done successfully, this is empty client account\n";
								break;
							case clsBankClient::svFailedAccountNumber:
								cout << "\nWithdrawl has not been done successfully, this Account number is not exist\n";
								break;

							}
						}
						else {
							cout << "\nInvalid withdrawl ammount.....!\n";
							cout << "\nYour Balance is " << Client.Balance;
							cout << "\nWithdrawl value is " << WithdrawlValue;
						}
					}
					else {
						cout << "\nOperation was cancelled....\n";
						repeat = 'n';
					}
				}
				else
				{
					cout << "\nInvalid withdrawl ammount.....!\n";
					cout << "\nYour Balance is " << Client.Balance;
					cout << "\nWithdrawl value is " << WithdrawlValue;
					cout << "\nDo you want to try another value? Y/N \n";
					cin >> repeat;
				}
			} while (tolower(repeat == 'y'));
		}
		else {
			cout << "\nThis account number is not exist, please enter a valid one: \n";
		}
	}

public:
	static void ShowWithdrawlScreen() {
		char repeat;
		do {
		_DrawScreenTilte("Withdrawl Screen", "*");
		cout << "\n\n-------------------------------------------------\n\n";
		_Withdrawl();
		cout << "\nDo you want to perform another withdrawl? Y/N\n";
		cin >> repeat;
		} while (tolower(repeat) == 'y');
	}

};

