#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsUser.h"
using namespace std;
class clsFindUserScreen:protected clsScreen
{
private:

	static void _Print(clsUser User) {
		cout << "\n\n--------------------------------------\n";
		cout << "User Card: \n";
		cout << left << setw(15) << "\nFirts Name: " << User.FirstName;
		cout << left << setw(15) << "\nLast Name: " << User.LastName;
		cout << left << setw(15) << "\nEmail: " << User.Email;
		cout << left << setw(15) << "\nPhone: " << User.Phone;
		cout << left << setw(15) << "\nUser Name: " << User.Username;
		cout << left << setw(15) << "\nPassword: " << User.Password;
		cout << left << setw(15) << "\nPermissions: " << to_string(User.Permissions);
		cout << "\n--------------------------------------\n";
	}

	static void _FindUser() {
		cout << "\nEnter the username of the user you want to update: \n";
		string username = clsInputValidate<string>::ReadString();
		if (!clsUser::isExistUser(username)) {
			cout << "\nSorry this username is not exist\n";
		}
		else {
			clsUser user = clsUser::Find(username);
			cout << "\nUser was found: \n";
			_Print(user);
		}
	}

public:

	static void ShowFindUserScreen() {
		char repeat;
		do {
		_DrawScreenTilte("Find User Screen", "*");
		_FindUser();
		cout << "\nDo you want to search another user? Y/N\n";
		cin >> repeat;
		} while (tolower(repeat) == 'y');
	}

};

