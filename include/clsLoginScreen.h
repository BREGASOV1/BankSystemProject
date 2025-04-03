#pragma once
#include<iostream>
#include"clsScreen.h"
#include"Global.h"
#include"clsInputValidate.h"
#include"clsMainMenue.h"
class clsLoginScreen :protected clsScreen
{

private:

	
	static bool _login() {
		short LoginAttemps = 0;
		cout << "\nEnter your username: \n";
		string username = clsInputValidate<string>::ReadString();
		cout << "\nEnter your password: \n";
		string password = clsInputValidate<string>::ReadString();
		CurrentUser = clsUser::Find(username, password);
		LoginAttemps++;
		while (CurrentUser.isEmpty()) {

			if (LoginAttemps == 3) {
				cout <<endl<< clsUtility::setw(50, "#") << endl;
				cout << "\ntoo many failed attemps, system is locked now.....\n\n";
				cout << clsUtility::setw(50, "#");
				return false;
			}

				
				cout << "\nIncorrect username or password, Try again..!\n";
				cout << "\nYou have " + to_string(3-LoginAttemps) + " attemps left\n";
				cout << "\nEnter your username: \n";
				string username = clsInputValidate<string>::ReadString();
				cout << "\nEnter your password: \n";
				string password = clsInputValidate<string>::ReadString();
				CurrentUser = clsUser::Find(username, password);
				LoginAttemps++;
				
			}
		CurrentUser.SaveLoginInLogFile();
		clsMainMenue::MainMenue();
	
		return true;

			
		
	}

	 

public:

	 static bool  ShowLoginScreen() {
		
		_DrawScreenTilte("Login Screen", "*");

		return _login();
		
	}
	 
	
};

