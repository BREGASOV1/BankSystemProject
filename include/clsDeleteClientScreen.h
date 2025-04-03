#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

class clsDeleteClientScreen:protected clsScreen
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

	static void _DeleteClient() {
		
		cout << "\nEnter the Account Number of the Client you want to delete:\n ";
		string AccountNumber = clsInputValidate<string>::ReadString();
		if (!clsBankClient::isExistClient(AccountNumber)) {
			cout << "\nThis account number is not exist\n";
			
		}
		else {
			clsBankClient DeleteClient = clsBankClient::Find(AccountNumber);
			cout << "\nAccount was found:\n";
			_Print(DeleteClient);
			cout << "\nAre you sure you want to delete this client?  Y/N \n ";
			char answer;
			cin >> answer;
			if (tolower(answer) == 'y') {
				DeleteClient.MarkClientToDelete();
				clsBankClient::enSaveResult SaveResult = DeleteClient.Save();

				switch (SaveResult)
				{
				case clsBankClient::svSavedSuccessfully:
					cout << "\nClient has been Deleted Successfully\n";
					_Print(DeleteClient);
					break;
				case clsBankClient::svFailedEmptyObject:
					cout << "\nClient has not been Deleted Successfully, it is empty\n";
					break;
				case clsBankClient::svFailedAccountNumber:
					cout << "\nClient has not been Deleted Successfully, it has invalid AccountNumber\n";
					break;
				default:
					break;
				}
			}
			
		}
	}

public:
	
	static void ShowDeleteClientScreen() {
		if (!clsScreen::AccessPermission(clsUser::pDeleteClient)) {
			return;
		}
		char repeat;
		do {
			clsScreen::_DrawScreenTilte("Delete Client Screen", "*");
			cout << "\n\n-------------------------------------------------\n";
			_DeleteClient();
			cout << "\nDo you want to delete another one ? Y/N \n";
			cin >> repeat;
		} while (tolower(repeat) == 'y');
	}
};

