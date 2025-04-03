#pragma once
#include<iostream>
#include"clsUtility.h"
#include"clsScreen.h"
#include"clsBankClient.h"
using namespace std;
class clsTransferLogScreen: protected clsScreen
{
	static void _PrintSingleTransferLog(clsBankClient::stTransferLog TransferLog) {
		cout << left;
		cout << "| " << setw(22) << TransferLog.TransferDateTime;
		cout << "| " << setw(18) << TransferLog.SenderAccountNumber;
		cout << "| " << setw(18) << TransferLog.ReceiverAccountNumber;
		cout << "| " << setw(12) << to_string(TransferLog.amount);
		cout << "| " << setw(15) << to_string(TransferLog.SenderNewBalance);
		cout << "| " << setw(15) << to_string(TransferLog.ReceiverNewBalance);
		cout << "| " << setw(10) << TransferLog.username<<endl;


	}

public:

	static void ShowTransfersScree() {
		
		vector <clsBankClient::stTransferLog> vTransferLog = clsBankClient::GetTransfersLog();
		string title = "[" + to_string(vTransferLog.size()) + "] Transfer(s)";
		_DrawScreenTilte("Transfers Log Screen", "*", title);
		if (vTransferLog.size() == 0)
		{
			cout << "\nWe have no users...!!!\n";

		}
		else {
			cout << "\n" << clsUtility::setw(60, "__") << "\n\n\n";
			cout << left;
			cout << "| " << setw(22) << "Date/Time";
			cout << "| " << setw(18) << "Sen.AccountNum";
			cout << "| " << setw(18) << "Rec.AccountNum";
			cout << "| " << setw(12) << "Amount";
			cout << "| " << setw(15) << "Sen.Balance";
			cout << "| " << setw(15) << "Rec.Balance";
			cout << "| " << setw(10) << "Username";
			cout << "\n" << clsUtility::setw(60, "__") << "\n\n\n";
			for (clsBankClient::stTransferLog& TransferLog : vTransferLog)
				_PrintSingleTransferLog(TransferLog);
		}
		cout << "\n" << clsUtility::setw(60, "__") << "\n\n\n";

	}

};

