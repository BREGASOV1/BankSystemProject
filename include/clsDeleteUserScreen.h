#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsUser.h"
using namespace std;
class clsDeleteUserScreen : protected clsScreen
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

	static void _DeleteUser() {
		cout << "\nEnter the username of the user you want to delete: \n";
		string username = clsInputValidate<string>::ReadString();
		if(!clsUser::isExistUser(username)) {
			cout << "\nSorry this username is not exist..... \n";
			
		}
		else {
			clsUser user = clsUser::Find(username);
			cout << "\nUser was found: \n";
			_Print(user);
			cout << "\nAre you sure you  want to delete this user? Y/N \n";
			char answer;
			cin >> answer;
			if (tolower(answer) == 'y') {
				user.MarkUserToDelete();
				clsUser::enSaveResult  SaveResult = user.Save();
				cout << "\nUser has been Deleted Successfully\n";
				_Print(user);


			}
			else
				cout << "\nOperation was cancelled..!!\n";
		}
	}

public:

	static void ShowDeleteUsersScreen() {
		char repeat;
		do {
			_DrawScreenTilte("Delete User Screen", "*");
			_DeleteUser();
			cout << "\nDo you want to delete another one ? Y/N \n";
			cin >> repeat;
		} while (tolower(repeat) == 'y');
	}
};

