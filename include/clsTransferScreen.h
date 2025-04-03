#pragma once
#include<iostream>
#include"clsInputValidate.h"
#include"clsBankClient.h"
#include"clsUtility.h"
#include"clsScreen.h"
using namespace std;
class clsTransferScreen :protected clsScreen
{
private:
	static void _Print(clsBankClient Client) {
		cout << clsUtility::setw(20, "_") << endl;
		cout <<"\nFull Name:      "<< Client.GetFullName();
		cout << "\nAccount Number: " << Client.GetAccountNumber();
		cout << "\nBalance:        " << Client.Balance<<"\n\n";
		cout << clsUtility::setw(20, "_") << endl;
	}

	static void _Transfer() {
		char repeat = 'n';
		cout << "\nEnter the Account Number of the Account you want transfer from: ";
		string SenderAccountNumber = clsInputValidate<string>::ReadString();
		cout << "\nEnter the Account Number of the Account you want transfer to: ";
		string ReceiverAccountNumber = clsInputValidate<string>::ReadString();
		if (clsBankClient::isExistClient(ReceiverAccountNumber) && clsBankClient::isExistClient(SenderAccountNumber))
		{

			clsBankClient SenderClient = clsBankClient::Find(SenderAccountNumber);
			cout << "\nFrom: \n";
			_Print(SenderClient);
			cout << "\nTo: \n";
			clsBankClient ReceiverClient = clsBankClient::Find(ReceiverAccountNumber);
			_Print(ReceiverClient);
			do {
				cout << "\nPlease enter the amount you want to transfer: ";
				double amount = clsInputValidate<double>::ReadNumber();
				if (amount <= SenderClient.Balance) {
					cout << "\nAre you sure you want to transfer " << to_string(amount) << " from " << SenderClient.GetFullName() << " to " << ReceiverClient.GetFullName() << " ? Y/N \n";
					char answer;
					cin >> answer;
					if (tolower(answer) == 'y') {
						if (SenderClient.TransferTo(amount, ReceiverClient)) {

							cout << "\nTransfer has been done successfully...\n";
							_Print(SenderClient);
							_Print(ReceiverClient);
							repeat = 'n';
						}
						else {
							cout << "\nTransfer has not been done successfully......!!\n";
							repeat = 'n';
						}
					}
					else {
						cout << "\nOperation was cancelled....\n";
						repeat = 'n';
					}
				}
				else {

					cout << "\nDo you want to enter another amount? Y/N \n";
					cin >> repeat;
				}
			} while (tolower(repeat) == 'y');
		}
		else
		{
			cout << "\nOne or both of the account numbers you entered are not exist....!\n";
			repeat = 'n';
		}
	}
public:
	static void TransferScreen() {
		char repeat;
		do {
			_DrawScreenTilte("Transfer Screen", "*");
			_Transfer();
			cout << "\nDo you want to do another Transfer? Y/N\n";
			cin >> repeat;
		} while (tolower(repeat) == 'y');
	}
};

