#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsUser.h"
using namespace std;
class clsUpdateUserScreen:protected clsScreen
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

	static void _ReadUserPrmissions(clsUser& User) {
		User.Permissions = 0;
		cout << "\nPermissions:\n";
		cout << "\nDo you want to give user full permissions? Y/N\n";
		char answer;
		cin >> answer;
		if (tolower(answer) == 'y')
			User.Permissions = -1;
		else {
			clsUser::enMainMenuePermissions Permission;
			char answer;
			cout << "\Do you want to give access to Show Clients? Y/N ";
			cin >> answer;
			(tolower(answer) == 'y') ? User.AddPermission(clsUser::pListClients) : User.AddPermission(clsUser::pNothing);
			cout << "\Do you want to give access to Add Client? Y/N ";
			cin >> answer;
			(tolower(answer) == 'y') ? User.AddPermission(clsUser::pAddClients) : User.AddPermission(clsUser::pNothing);
			cout << "\Do you want to give access to Delete Client? Y/N ";
			cin >> answer;
			(tolower(answer) == 'y') ? User.AddPermission(clsUser::pDeleteClient) : User.AddPermission(clsUser::pNothing);
			cout << "\Do you want to give access to Update Client? Y/N ";
			cin >> answer;
			(tolower(answer) == 'y') ? User.AddPermission(clsUser::pUpdateClient) : User.AddPermission(clsUser::pNothing);
			cout << "\Do you want to give access to Find Client? Y/N ";
			cin >> answer;
			(tolower(answer) == 'y') ? User.AddPermission(clsUser::pFindClient) : User.AddPermission(clsUser::pNothing);
			cout << "\Do you want to give access to Tansactions? Y/N ";
			cin >> answer;
			(tolower(answer) == 'y') ? User.AddPermission(clsUser::pTransactions) : User.AddPermission(clsUser::pNothing);
			cout << "\Do you want to give access to Manage Users? Y/N ";
			cin >> answer;
			(tolower(answer) == 'y') ? User.AddPermission(clsUser::pManageUsers) : User.AddPermission(clsUser::pNothing);
			cout << "\Do you want to give access to deal with Currency menu? Y/N ";
			cin >> answer;
			(tolower(answer) == 'y') ? User.AddPermission(clsUser::pCurrency) : User.AddPermission(clsUser::pNothing);
			cout << "\Do you want to give access to view Login Registers list? Y/N ";
			cin >> answer;
			(tolower(answer) == 'y') ? User.AddPermission(clsUser::pLoginRegisterList) : User.AddPermission(clsUser::pNothing);


		}
	}

	static void _ReadUserInfo(clsUser& User) {
		char answer;
		cout << "\nDo you want to update First Name? Y/N \n";
		cin >> answer;
		if (tolower(answer) == 'y') {
			cout << "\nEnter user First Name:  ";
			User.FirstName = clsInputValidate<string>::ReadString();
		}
		cout << "\nDo you want to update Last Name? Y/N \n";
		cin >> answer;
		if (tolower(answer) == 'y') {
			cout << "\nEnter user Last Name:  ";
			User.LastName = clsInputValidate<string>::ReadString();
		}
		cout << "\nDo you want to update Email? Y/N \n";
		cin >> answer;
		if (tolower(answer) == 'y') {
			cout << "\nEnter user's email:  ";
			User.Email = clsInputValidate<string>::ReadString();
		}
		cout << "\nDo you want to update Phone? Y/N \n";
		cin >> answer;
		if (tolower(answer) == 'y') {
			cout << "\nEnter user's Phone:  ";
			User.Phone = clsInputValidate<string>::ReadString();
		}
		cout << "\nDo you want to update Password? Y/N \n";
		cin >> answer;
		if (tolower(answer) == 'y') {
			cout << "\nEnter user's Password:  ";
			User.Password = clsInputValidate<string>::ReadString();
		}
		cout << "\nDo you want to update Permissions? Y/N \n";
		cin >> answer;
		if (tolower(answer) == 'y') 
		_ReadUserPrmissions(User);
	}

	static void _Update() {
		cout << "\nEnter the username of the user you want to update: \n";
		string username = clsInputValidate<string>::ReadString();
		if (!clsUser::isExistUser(username)) {
			cout << "\nSorry this username is not exist...... \n";

		}
		else {
			clsUser user = clsUser::Find(username);
			cout << "\nUser was found: \n";
			_Print(user);
			cout << "\nAre you sure you  want to update this user info? Y/N \n";
			char answer;
			cin >> answer;
			if (tolower(answer == 'y')) {
				cout << "\nUpdating User: \n";
				_ReadUserInfo(user);
				clsUser::enSaveResult  SaveResult = user.Save();
				switch (SaveResult)
				{
				case clsUser::svSavedSuccessfully:
					cout << "\nUser has been updated successfully\n";
					_Print(user);
					break;
				case clsUser::svFailedEmptyObject:
					cout << "\nUser has not been updated Successfully, it is empty\n";
					break;
				case clsUser::svFailedAccountNumber:
					cout << "\nUser has not been updated Successfully, it has invalid user name or AccountNumber\n";
					break;
				default:
					break;
				}
			}
			else
				cout << "\nOperation was cancelled....!!\n";
		}
	}

public:

	static void ShowUpdateUserScreen() {
		char repeat;
		do {
		_DrawScreenTilte("Update User Screen", "*");
		_Update();
		cout << "\nDo you want to update another user? Y/N\n";
		cin >> repeat;
		} while (tolower(repeat) == 'y');
	}
};


