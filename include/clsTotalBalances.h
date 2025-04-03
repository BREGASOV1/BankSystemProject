#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
using namespace std;
class clsTotalBalances:protected clsScreen
{
private:
	static void _PrintSingleClient(clsBankClient Client) {
		cout << left;
		cout << "| " << setw(20) << Client.GetAccountNumber();
		cout << "| " << setw(15) << Client.GetFullName();
		cout << "| " << setw(20) << Client.Balance << endl;

	}

	static void _ShowClientsBalances() {
		vector<clsBankClient> vClients = clsBankClient::GetClientList();
		cout << "\n" << clsUtility::setw(55, "__") << "\n\n";
		cout << left;
		cout << "| " << setw(20) << "Account Number";
		cout << "| " << setw(15) << "Client Name";
		cout << "| " << setw(20) << "Balance";
		cout << "\n" << clsUtility::setw(55, "__") << "\n\n";
		for (clsBankClient& Client : vClients) {
			_PrintSingleClient(Client);
		}
		cout << "\n" << clsUtility::setw(55, "__") << "\n\n";
		cout << "\nTotal Balances is " << clsBankClient::TotalBalances();
	}

	
public:
	static void ShowTotalBalancesScreen() {
		_DrawScreenTilte("Total Balances", "*", to_string(clsBankClient::ClientsCount()) + " Client(s)");
		_ShowClientsBalances();
	}

};

