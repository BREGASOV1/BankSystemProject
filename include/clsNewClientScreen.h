#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsBankClient.h"
using namespace std;
class clsNewClientScreen:protected clsScreen
{
private:
	static bool _AddAnotherOne;
	static void  _EnterClientData(clsBankClient& Client) {
		cout << "\nEnter first name:...\n";
		Client.FirstName = clsInputValidate<string>::ReadString();
		cout << "\nEnter last name:...\n";
		Client.LastName = clsInputValidate<string>::ReadString();
		cout << "\nEnter Email:...\n";
		Client.Email = clsInputValidate<string>::ReadString();
		cout << "\nEnter Phone:...\n";
		Client.Phone = clsInputValidate<string>::ReadString();
		cout << "\nEnter PIN:...\n";
		Client.PIN = clsInputValidate<string>::ReadString();
		cout << "\nEnter Balance:...\n";
		Client.Balance = clsInputValidate<double>::ReadNumber();



	}

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
	
	static bool _AddNewClient() {
		char repeat;
		cout << "\nAdding New Client: \n";
		do {
			cout << "\nEnter New Client Account Number: \n";
			string AccountNumber = clsInputValidate<string>::ReadString();
			if (clsBankClient::isExistClient(AccountNumber)) {
				cout << "\This Account number is already used, Do you want to try another one? Y/N \n";
				cin >> repeat;	
			}
			else {
				cout << "\nEnter new Client data: \n";
				clsBankClient NewClient = clsBankClient::CreatNewClient(AccountNumber);
				_EnterClientData(NewClient);
				clsBankClient::enSaveResult SaveResult = NewClient.Save();

				switch (SaveResult)
				{
				case clsBankClient::svSavedSuccessfully:
					cout << "\nClient has been Added Successfully\n";
					_Print(NewClient);
					break;
				case clsBankClient::svFailedEmptyObject:
					cout << "\nClient has not been Added Successfully, it is empty\n";
					break;
				case clsBankClient::svFailedAccountNumber:
					cout << "\nClient has not been Added Successfully, it has invalid AccountNumber\n";
					break;
				default:
					break;
				}
				return true;
			}
		} while (tolower(repeat) == 'y');
		return false;
		

	}

public:

	static void ShowAddClientScreen() {
		if (!(clsScreen::AccessPermission(clsUser::pAddClients))) {
			return;
		}
		char repeat = 'N';
		do {
			clsScreen::_DrawScreenTilte("Add New Client Screen", "*");
			cout << "\n\n-------------------------------------------------\n\n";
			
			if (_AddNewClient()) {
				cout << "\nDo you want to add another client? Y/N \n";
				cin >> repeat;
			}
		} while (tolower(repeat == 'y'));
	}

};

