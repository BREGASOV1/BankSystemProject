#pragma once
#include<iostream>
#include"clsDepositScreen.h"
#include"clsInputValidate.h"
#include"clsWithdrawlScreen.h"
#include"clsTotalBalances.h"
#include"clsTransferScreen.h"
#include"clsTransferLogScreen.h"
using namespace std;
class clsTransactionMenue:protected clsScreen
{
private:
	enum enTransatcionMenueAction { Deposit = 1, WithDrawl, TotalBalances, Transfer, TransferLog, MainMenue };

	static enTransatcionMenueAction _ReadTransactionMenueChoice() {
		return (enTransatcionMenueAction)clsInputValidate<short>::ReadNumberBetween(1, 6, "\nPlease enter a number between 1 and 6\n");
	}

	static void _BackToTransactionMenue() {
		
		cout << "\npress any key to go back to Transaction menu......\n";
		system("pause>0");
		TransactionMenue();
		
	}

	static void _DepositeScreen() {
		clsDepositScreen::ShowDepositScreen();
	}

	static void _WithdrawlScreen() {
		clsWithdrawlScreen::ShowWithdrawlScreen();
	}

	static void _TotalBalancesScreen() {
		clsTotalBalances::ShowTotalBalancesScreen();
	}
	
	
	static void _TransferScreen() {
		clsTransferScreen::TransferScreen();
	}

	static void _TransferLogScreen() {
		clsTransferLogScreen::ShowTransfersScree();
	}

	static void _PerformTransactionMenueAction(enTransatcionMenueAction TransactionMenueAction) {
		switch (TransactionMenueAction)
		{
		case clsTransactionMenue::Deposit:
			_DepositeScreen();
			_BackToTransactionMenue();
			break;
		case clsTransactionMenue::WithDrawl:
			_WithdrawlScreen();
			_BackToTransactionMenue();
			break;
		case clsTransactionMenue::TotalBalances:
			_TotalBalancesScreen();
			_BackToTransactionMenue();
			break;
		case clsTransactionMenue::Transfer:
			_TransferScreen();
			_BackToTransactionMenue();
			break;
		case clsTransactionMenue::TransferLog:
			_TransferLogScreen();
			_BackToTransactionMenue();
			break;
		case clsTransactionMenue::MainMenue:
			break;
	
		}
	}

public:

	static void TransactionMenue() {
		if (!clsScreen::AccessPermission(clsUser::pTransactions)) {
			cout << "\nPress any key to go back to main menue......\n";
			system("pause > 0");
			return;
		}

		clsScreen::_DrawScreenTilte("Transactions", "*");
		cout <<clsUtility::setw(20, " ") << clsUtility::setw(38, "==") << "\n\n";
		cout <<clsUtility::setw(13, "  ") << clsUtility::setw(13, "  ") << "Transactions Menue Screen" << "\n\n";
		cout <<clsUtility::setw(20, " ") << clsUtility::setw(38, "==") << "\n";
		cout << clsUtility::setw(3, "	")<<clsUtility::setw(3, "	") << "[1] Deposit." << "\n";
		cout << clsUtility::setw(3, "	") << clsUtility::setw(3, "	") << "[2] Withdrawl." << "\n";
		cout << clsUtility::setw(3, "	") << clsUtility::setw(3, "	") << "[3] Total Balances." << "\n";
		cout << clsUtility::setw(3, "	") << clsUtility::setw(3, "	") << "[4] Transfer Screen." << "\n";
		cout << clsUtility::setw(3, "	") << clsUtility::setw(3, "	") << "[5] Transfer Log." << "\n";
		cout << clsUtility::setw(3, "	") << clsUtility::setw(3, "	") << "[6] Main Menue." << "\n";
		
		cout << clsUtility::setw(20, " ") << clsUtility::setw(38, "==") << "\n";
		cout << "\nChoose what do you want to do [1,6]:\n";

		_PerformTransactionMenueAction(_ReadTransactionMenueChoice());


	}

};

