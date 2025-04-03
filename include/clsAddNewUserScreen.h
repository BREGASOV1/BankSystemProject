#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsUser.h"
#include"clsInputValidate.h"
class clsAddNewUserScreen:protected clsScreen
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
	static void _ReadUserPrmissions(clsUser & User) {
		cout << "\nPermissions:\n";
		cout << "\nDo you want to give user full permissions? Y/N\n";
		char answer;
		cin >> answer;
		if (tolower(answer) == 'y')
			User.Permissions = -1;
		else {
			User.Permissions = 0;
			clsUser::enMainMenuePermissions Permission ;
			char answer;
			cout << "\Do you want to give access to Show Clients? Y/N ";
			cin >> answer;
			(tolower(answer) == 'y') ? User.AddPermission(clsUser::pListClients): User.AddPermission(clsUser::pNothing);
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
		cout << "\nEnter user First Name:  ";
		User.FirstName = clsInputValidate<string>::ReadString();
		cout << "\nEnter user Last Name:  ";
		User.LastName = clsInputValidate<string>::ReadString();
		cout << "\nEnter user's email:  ";
		User.Email = clsInputValidate<string>::ReadString();
		cout << "\nEnter user's Phone:  ";
		User.Phone = clsInputValidate<string>::ReadString();
		cout << "\nEnter user's Password:  ";
		User.Password = clsInputValidate<string>::ReadString();
		_ReadUserPrmissions(User);
	}

	static bool _AddNewUser() {
		char repeat;
		cout << "\nAdding New User: \n";
		do {
			cout << "\nEnter the username of the new user: \n";
			string username = clsInputValidate<string>::ReadString();
			if (clsUser::isExistUser(username)) {
				cout << "\nSorry this username is already used......\n";
				cout << "\nDo you want to try again? Y/N\n";
				cin >> repeat;
			}
			else {
				clsUser NewUser = clsUser::CreatNewUser(username);
				cout << "\nPlease fill new user info: \n";
				_ReadUserInfo(NewUser);
				clsUser::enSaveResult  SaveResult = NewUser.Save();
				switch (SaveResult)
				{
				case clsUser::svSavedSuccessfully:
					cout << "\nUser has been Added Successfully\n";
					_Print(NewUser);
					break;
				case clsUser::svFailedEmptyObject:
					cout << "\nUser has not been Added Successfully, it is empty\n";
					break;
				case clsUser::svFailedAccountNumber:
					cout << "\nUser has not been Added Successfully, it has invalid AccountNumber\n";
					break;
				default:
					break;
				}
				return true;

			}

			
		} while (tolower(repeat) == 'y');
		return false;
	}
public:
	static void ShowAddNewUserScreen() {
		char repeat = 'n';
		do {
			_DrawScreenTilte("Add New User Screen", "*");

			if (_AddNewUser()) {
				cout << "\nDo you want to add another user? Y/N \n";
				cin >> repeat;
			}
		} while (tolower(repeat == 'y'));
	}
	
};

