#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
using namespace std;
class clsUpdateClientScreen :protected clsScreen
{
private:

	static void  _EnterClientData(clsBankClient& Client) {
		char answer;
		cout << "\nDo you want to update First Name? Y/N \n";
		cin >> answer;
		if (tolower(answer) == 'y') {
			cout << "\nEnter first name:...\n";
			Client.FirstName = clsInputValidate<string>::ReadString();
		}
	
		cout << "\nDo you want to update Last Name? Y/N \n";
		cin >> answer;
		if (tolower(answer) == 'y') {
			cout << "\nEnter last name:...\n";
			Client.LastName = clsInputValidate<string>::ReadString();
		}
		
		cout << "\nDo you want to update Email? Y/N \n";
		cin >> answer;
		if (tolower(answer) == 'y') {
			cout << "\nEnter Email:...\n";
			Client.Email = clsInputValidate<string>::ReadString();
		}
		
		cout << "\nDo you want to update Phone? Y/N \n";
		cin >> answer;
		if (tolower(answer) == 'y') {
			cout << "\nEnter Phone:...\n";
			Client.Phone = clsInputValidate<string>::ReadString();
		}
		
		cout << "\nDo you want to update PIN? Y/N \n";
		cin >> answer;
		if (tolower(answer) == 'y') {
			cout << "\nEnter PIN:...\n";
			Client.PIN = clsInputValidate<string>::ReadString();
		}
		
		cout << "\nDo you want to update Balance? Y/N \n";
		cin >> answer;
		if (tolower(answer) == 'y') {
			cout << "\nEnter Balance:...\n";
			Client.Balance = clsInputValidate<double>::ReadNumber();
		}



	}

	static void _Print(clsBankClient Client) {
		cout << "\n\n--------------------------------------\n";
		cout << "Client Card: \n";
		cout << left << setw(15) << "\nFirts Name: " << Client.FirstName;
		cout << left << setw(15) << "\nLast Name: " << Client.LastName;
		cout << left << setw(15) << "\nEmail: " << Client.Email;
		cout << left << setw(15) << "\nPhone: " << Client.Phone;
		cout << left << setw(15) << "\nAccount NO: " << Client.GetAccountNumber();
		cout << left << setw(15) << "\nPIN: " << Client.PIN;
		cout << left << setw(15) << "\nBalance: " << Client.Balance;
		cout << "\n--------------------------------------\n";
	}

	static void _UpdateClient() {
		string AccountNumber;
		cout << "\nEnter the Account Number of Wanted Account\n";
		AccountNumber = clsInputValidate<string>::ReadString();
		if (!(clsBankClient::isExistClient(AccountNumber))) {
			cout << "\nThis account is not exist.....!\n";
			
		}
		else {
			cout << "\nAccount was found....\n";
			clsBankClient Client = clsBankClient::Find(AccountNumber);
			_Print(Client);
			cout << "\nUpdate Client data: \n";
			_EnterClientData(Client);
			clsBankClient::enSaveResult SaveResult = Client.Save();
			switch (SaveResult)
			{
			case clsBankClient::svSavedSuccessfully:
				cout << "\nClient has been updated successfully....\n";
				break;
			case clsBankClient::svFailedEmptyObject:
				cout << "\nClient has not been updated successfully, Empty data....\n";
				break;
			default:
				break;
			}

		}
	}

public:
	static void ShowUpdateClientScreen() {
		if (!clsScreen::AccessPermission(clsUser::pUpdateClient)) {
			return;
		}
		char repeat;
		do {

			clsScreen::_DrawScreenTilte("Update Client Screen", "*");
			cout << "\n\n-------------------------------------------------\n\n";
			_UpdateClient();
			cout << "\nDo you want to update another Client? Y/N\n";
			cin >> repeat;
		} while (tolower(repeat) == 'y');
	}
};