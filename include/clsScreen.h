#pragma once
#include<iostream>
#include"clsUtility.h"
#include"clsUser.h"
#include"Global.h"
#include"clsDate.h"
#include<iomanip>
using namespace std;
class clsScreen
{
protected:
	static void _DrawScreenTilte(string Title, string delim = "=", string subTitle ="") {
	
		system("cls");

		cout << clsUtility::setw(4, "	")<<clsUtility::setw(50, delim) << "\n\n";
		cout <<clsUtility::setw(25, "  ") << Title << "\n";
		if(subTitle !="")
			cout << clsUtility::setw(25, "  ") << subTitle << "\n";
		cout  <<endl<<clsUtility::setw(4, "	")<< clsUtility::setw(50, delim) << "\n";
		cout << clsUtility::setw(4, "	") << "User: " << CurrentUser.Username<<endl;
		cout << clsUtility::setw(4, "	") << "Date: " << clsDate::DateToString(clsDate())<<"\n\n"<<endl;


	}

	static bool AccessPermission(clsUser::enMainMenuePermissions MainMenuePermission) {
		if (!CurrentUser.CheckPermission(MainMenuePermission)) {
			_DrawScreenTilte("Access Denied", "*");
			cout << "\n\t\t\t\tYou cannot access this action\n";
			cout << "\n\t\t\t\tConatct your admin\n";
			return false;
			}
		return true;

	}

};

