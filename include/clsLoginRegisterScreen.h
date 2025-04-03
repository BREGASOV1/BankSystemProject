#pragma once
#include<iostream>
#include"clsUtility.h"
#include"clsScreen.h"
using namespace std;
class clsLoginRegisterScreen:protected clsScreen
{
	static void _PrintSingleLoginRegister(clsUser::stLoginRegister LoginRegister) {
		cout << left;
		cout << "| " << setw(22) << LoginRegister._LoginDate;
		cout << "| " << setw(15) << LoginRegister._Username;
		cout << "| " << setw(15) << LoginRegister._Password;
		cout << "| " << setw(20) << LoginRegister._Permissions<<endl;
		
	}
	
public:

	static void ShowLoginRegisterScree() {
		if (!clsScreen::AccessPermission(clsUser::pLoginRegisterList)) {
			return;
		}
		
		vector <clsUser::stLoginRegister> vLoginRegisters = clsUser::GetLoginRegisters();
		string title = "[" + to_string(vLoginRegisters.size()) + "] Record(s)";
		_DrawScreenTilte("Login Register Screen", "*",title);
		if (vLoginRegisters.size() == 0)
		{
			cout << "\nWe have no users...!!!\n";

		}
		else {
			cout << "\n" << clsUtility::setw(58, "__") << "\n\n";
			cout << left;
			cout << "| " << setw(22) << "Date/Time";
			cout << "| " << setw(15) << "Username";
			cout << "| " << setw(15) << "Password";
			cout << "| " << setw(20) << "Permissions";
			cout << "\n" << clsUtility::setw(58, "__") << "\n\n";
			for (clsUser::stLoginRegister& LoginRegister : vLoginRegisters)
				_PrintSingleLoginRegister(LoginRegister);
		}
		cout << "\n" << clsUtility::setw(58, "__") << "\n\n\n";

	}
};

