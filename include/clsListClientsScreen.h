#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsBankClient.h"
class clsListClientsScreen :protected clsScreen
{
private:
	static void _PrintSingleClient(clsBankClient Client) {
		cout << left;
		cout << "| " << setw(20) << Client.GetAccountNumber();
		cout << "| " << setw(15) << Client.GetFullName();
		cout << "| " << setw(18) << Client.Phone;
		cout << "| " << setw(20) << Client.Email;
		cout << "| " << setw(10) << Client.PIN;
		cout << "| " << setw(20) << Client.Balance << endl;
	}

public:
	static void ShowClients() {
		if (!clsScreen::AccessPermission(clsUser::pListClients)) {
			return;
		}
		vector<clsBankClient> vClients = clsBankClient::GetClientList();
		string subTitle = "  [" + to_string(vClients.size()) + "] Client(s)";
		clsScreen::_DrawScreenTilte("Client List Screen", "*", subTitle);
		if (vClients.size() == 0)
			cout << "\nThere is no clients in our bank...!!\n";
		else {

			cout << "\n" << clsUtility::setw(55, "__") << "\n\n";
			cout << left;
			cout << "| " << setw(20) << "Account Number";
			cout << "| " << setw(15) << "Client Name";
			cout << "| " << setw(18) << "Phone";
			cout << "| " << setw(20) << "Email";
			cout << "| " << setw(10) << "PIN";
			cout << "| " << setw(20) << "Balance";
			cout << "\n" << clsUtility::setw(55, "__") << "\n\n";
			for (clsBankClient& Client : vClients) {
				_PrintSingleClient(Client);
			}
			cout << "\n" << clsUtility::setw(55, "__") << "\n\n";
		}

	}
		

		
	
	
};

