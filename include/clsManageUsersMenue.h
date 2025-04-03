#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsListUsersScreen.h"
#include"clsAddNewUserScreen.h"
#include"clsDeleteUserScreen.h"
#include"clsUpdateUserScreen.h"
#include"clsFindUserScreen.h"
class clsManageUsersMenue:protected clsScreen
{
private:

	enum enManageUsersMenueAction { ListUsers = 1, NewUser, DeleteUser, UpdateUser, FindUser, MainMenue };

	static enManageUsersMenueAction ReadManageUsersMenueAction() {
		return (enManageUsersMenueAction)clsInputValidate<short>::ReadNumberBetween(1, 6, "\nPlease choose an option between 1 and 6 \n");
	}
	
	static void _BackToManageUsersMenue() {
		cout << "\npress any key to go back to manage users screen......\n";
		system("pause>0");
		ManageUsersMenue();
	}

	static void _ListUsersSceen() {
		clsListUsersScreen::ShowListUsersScreen();
	}

	static void _NewUserScreen() {
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _DeleteUserScreen() {
		clsDeleteUserScreen::ShowDeleteUsersScreen();
	}

	static void _UpdateUserScreen() {
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _FindUserScreen() {
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersMenueAction(enManageUsersMenueAction ManageUsersAction) {
		switch (ManageUsersAction)
		{
		case clsManageUsersMenue::ListUsers:
			_ListUsersSceen();
			_BackToManageUsersMenue();
			break;
		case clsManageUsersMenue::NewUser:
			_NewUserScreen();
			_BackToManageUsersMenue();
			break;
		case clsManageUsersMenue::DeleteUser:
			_DeleteUserScreen();
			_BackToManageUsersMenue();
			break;
		case clsManageUsersMenue::UpdateUser:
			_UpdateUserScreen();
			_BackToManageUsersMenue();
			break;
		case clsManageUsersMenue::FindUser:
			_FindUserScreen();
			_BackToManageUsersMenue();
			break;
		case clsManageUsersMenue::MainMenue:
			break;
		
		}
	}

public:

	static void ManageUsersMenue() {
		if (!clsScreen::AccessPermission(clsUser::pManageUsers)) {
			cout << "\nPress any key to go back to main menue......\n";
			system("pause > 0");
			return;
		}
		_DrawScreenTilte("Manage Users Screen", "*");
		cout <<clsUtility::setw(20, " ")   <<clsUtility::setw(38, "==") << "\n\n";
		cout <<clsUtility::setw(13, "  ")  <<clsUtility::setw(13, "  ") << "Manage Users Menue" << "\n\n";
		cout <<clsUtility::setw(20, " ")   <<clsUtility::setw(38, "==") << "\n";
		cout <<clsUtility::setw(3, "	") <<clsUtility::setw(3, "	") << "[1] Show Users List." << "\n";
		cout <<clsUtility::setw(3, "	") <<clsUtility::setw(3, "	") << "[2] Add New User." << "\n";
		cout <<clsUtility::setw(3, "	") <<clsUtility::setw(3, "	") << "[3] Delete User." << "\n";
		cout <<clsUtility::setw(3, "	") <<clsUtility::setw(3, "	") << "[4] Update User Info." << "\n";
		cout <<clsUtility::setw(3, "	") <<clsUtility::setw(3, "	") << "[5] Find User." << "\n";
		cout <<clsUtility::setw(3, "	") <<clsUtility::setw(3, "	") << "[6] MainMenue." << "\n";
		cout <<clsUtility::setw(20, " ")   <<clsUtility::setw(38, "==") << "\n";
		cout << "\nChoose which action you want to perform [1,6]\n";
		_PerformManageUsersMenueAction(ReadManageUsersMenueAction());
	}
};

