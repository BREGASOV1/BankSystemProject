#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsUser.h"
using namespace std;
class clsListUsersScreen:protected clsScreen
{

private:
	static void _PrintSingleUser(clsUser User) {
		cout << left;
		cout << "| " << setw(20) << User.Username;
		cout << "| " << setw(15) << User.GetFullName();
		cout << "| " << setw(18) << User.Phone;
		cout << "| " << setw(20) << User.Email;
		cout << "| " << setw(20) << User.Password;
		cout << "| " << setw(20) << User.Permissions << endl;
	}
	
static void _ShowUsers() {
	vector<clsUser> vUsers = clsUser::GetUsersList();
	if (vUsers.size() == 0)
	{
		cout << "\nWe have no users...!!!\n";

	}
	else {
		cout << "\n" << clsUtility::setw(58, "__") << "\n\n";
		cout << left;
		cout << "| " << setw(20) << "Uername";
		cout << "| " << setw(15) << "Full Name";
		cout << "| " << setw(18) << "Phone";
		cout << "| " << setw(20) << "Email";
		cout << "| " << setw(20) << "Password";
		cout << "| " << setw(20) << "Permissions";
		cout << "\n" << clsUtility::setw(58, "__") << "\n\n";
		for (clsUser& User : vUsers)
			_PrintSingleUser(User);
	}
	cout << "\n" << clsUtility::setw(58, "__") << "\n\n\n";
}
public:
	static void ShowListUsersScreen(){
		_DrawScreenTilte("List Users Screen", "*", "[" + to_string(clsUser::UsersCount()) + "] User(s)");
		_ShowUsers();
	}
};

