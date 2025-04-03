#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include"clsPerson.h"
#include"clsString.h"
using namespace std;
class clsUser:public clsPerson
{
private:
	
	enum enUserMod{ _Empty, _Update,_New, _Delete};
	string _Password;
	string _Username;
	enUserMod _UserMod;
	short _Permissions;
	string _loginDate;
	
			   


	static clsUser _ConvertLineToUser(string line) {
		vector <string> vUsersData = clsString::SplitString(line, "#//#");
		vUsersData[5] = clsUtility::DecryptText(vUsersData[5], 2);
		return clsUser(_Update, vUsersData[0], vUsersData[1], vUsersData[2], vUsersData[3],
			vUsersData[4], vUsersData[5], stoi(vUsersData[6]));

	}

	string _ConvertUserToLineInLoginFile() {
		string line = "";
		line += clsDate::DateToString(clsDate()) + " - ";
		line += clsDate::GetSystemTime() + "#//#";
		line += Username + "#//#";
		Password = clsUtility::EncryptText(Password, 25);
		line += Password + "#//#";
		line += to_string(Permissions);
		return line;

	}
	

	static vector<clsUser> _StoreFileInUsersVector() {
		fstream File;
		vector<clsUser> vUsers;
		string line;
		File.open("Users.txt", ios::in);
		if (File.is_open()) {
			while (getline(File, line))
			{
				if (line != "")
					vUsers.push_back(_ConvertLineToUser(line));

			}
		}
		File.close();
		return vUsers;
	}

	 string _ConvertUserRecordIntoLine(clsUser User) {
		string line = "";
		line += User.FirstName + "#//#";
		line += User.LastName + "#//#";
		line += User.Email + "#//#";
		line += User.Phone + "#//#";
		line += User._Username + "#//#";
		
		line += clsUtility::EncryptText(User._Password, 2) + "#//#";
		line += to_string(User._Permissions);

		return line;
	}

	 void _StoreVectorOfUsersInFile(vector<clsUser> vUsers) {
		fstream File;
		File.open("Users.txt", ios::out);
		if (File.is_open()) {
			for (clsUser User : vUsers)
			{
				if (User._UserMod != _Empty && User._UserMod != _Delete) {
					
					File << _ConvertUserRecordIntoLine(User) << endl;
				}
			}
		}
		File.close();

	}

	

	static clsUser _EmptyUser() {
		return clsUser(_Empty, "", "", "", "", "", "", 0);
	}

	void _update() {
		vector<clsUser> vUsers = _StoreFileInUsersVector();
		for (clsUser& User : vUsers) {
			if (User.Username == this->Username) {
				User = *this;
				break;
			}
		}

		_StoreVectorOfUsersInFile(vUsers);
	}

	void _delete() {
		vector<clsUser> vUsers = _StoreFileInUsersVector();
		for (clsUser& User : vUsers) {
			if (User.Username == this->Username) {
				User = *this;
				break;
			}
		}
		*this = _EmptyUser();
		_StoreVectorOfUsersInFile(vUsers);

	}

	void _AddNew() {
		string NewUser = _ConvertUserRecordIntoLine(*this);
		fstream File;
		File.open("Users.txt", ios::app);
		if (File.is_open()) {
			if (NewUser != "")
				File << NewUser << endl;
		}
		File.close();
	}

	

public:
	

	struct stLoginRegister {
		string _LoginDate;
		string _Username;
		short _Permissions;
		string _Password;
	};

	clsUser(enUserMod UserMod, string FirstName, string LastName, string Email, string Phone, string username, string password, short permission)
		:clsPerson(FirstName, LastName, Email, Phone) {
		_UserMod = UserMod;
		_Username = username;
		_Password = password;
		_Permissions = permission;
	}

	void SetUsername(string username) {
		_Username = username;
	}
	string GetUsername() {
		return _Username;
	}
	__declspec(property(get = GetUsername, put = SetUsername))string Username;

	void SetPassword(string password) {
		_Password = password;
	}
	string GetPassword() {
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword))string Password;

	void SetPermissions(short permissions) {
		_Permissions = permissions;
	}
	short GetPermissions() {
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions))short Permissions;

	string GetLoginDate() {
		return _loginDate;
	}

	void MarkUserToDelete() {

		this->_UserMod = _Delete;

	}

	static clsUser EmptyCurrentUser() {
		return _EmptyUser();
	}

	bool isEmpty() {
		return (_UserMod == _Empty);
	}

	static clsUser CreatNewUser(string username) {
		return clsUser(_New, "", "", "", "", username, "", 0);
	}

	static clsUser Find(string Username) {
		vector <clsUser> vUsers;
		fstream File;
		string line;
		File.open("RequiredFiles/Users.txt", ios::in);
		bool temp = File.is_open();
		if (File.is_open()) {
			while (getline(File, line)) {
				if (line != "") {
					clsUser User = _ConvertLineToUser(line);
					if (User.GetUsername() == Username) {
						File.close();
						User._UserMod = _Update;
						return User;
					}
					vUsers.push_back(User);

				}
			}
		}
		File.close();
		return _EmptyUser();


	}

	static clsUser Find(string Username, string Password) {
		vector <clsUser> vUsers;
		fstream File;
		string line;
		File.open("RequiredFiles/Users.txt", ios::in);
		if (File.is_open())
			while (getline(File, line)) {
				clsUser User = _ConvertLineToUser(line);
				if (User.GetUsername() == Username && User.Password == Password) {
					File.close();
					User._UserMod = _Update;
					return User;
				}
				vUsers.push_back(User);

			}
		File.close();
		return _EmptyUser();


	}

	static  bool isExistUser(string username) {
		clsUser Client = clsUser::Find(username);
		return !(Client.isEmpty());

	}

	static vector<clsUser> GetUsersList() {
		return _StoreFileInUsersVector();
	}

	static stLoginRegister ConvertLineToLoginRegister(string line) {
		vector <string> vLoginRegister = clsString::SplitString(line, "#//#");
		stLoginRegister LoginRegister;

		LoginRegister._LoginDate = vLoginRegister[0];
		LoginRegister._Username = vLoginRegister[1];
		LoginRegister._Password = clsUtility::DecryptText(vLoginRegister[2], 25);
		LoginRegister._Permissions = stoi(vLoginRegister[3]);
		return LoginRegister;
	}

	static vector<stLoginRegister> StoreLoginRegisterFileInVector() {
		vector<stLoginRegister> vLoginRegisters;
		fstream File;
		string line;
		File.open("LoginRegister.txt", ios::in);
		while (getline(File, line)) {
			if (line != "")
				vLoginRegisters.push_back(ConvertLineToLoginRegister(line));
		}
		File.close();
		return vLoginRegisters;

	}

	static vector<stLoginRegister> GetLoginRegisters() {
		return StoreLoginRegisterFileInVector();
	}

	static short UsersCount() {
		return GetUsersList().size();
	}

	 string GetFullName() {
		return  clsPerson::FirstName + " " + clsPerson::LastName;
	}

	 void SaveLoginInLogFile() {
		 string line = _ConvertUserToLineInLoginFile();
		 fstream File;
		 File.open("LoginRegister.txt", ios::out | ios::app);
		 if (File.is_open()) {
			 if (line != "")
				 File << line << endl;
		 }

		 File.close();

	 }



	 enum enMainMenuePermissions {
		 pNothing = 0,
		 pAll = -1,
		 pListClients = 1, pAddClients = 2, pDeleteClient = 4,
		 pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64,
		 pCurrency = 128, pLoginRegisterList = 256
	 };

	 void AddPermission(enMainMenuePermissions Permission) {
		 _Permissions += Permission;
	 }

	 bool CheckPermission(enMainMenuePermissions MainMenueChoice) {
		 return (this->Permissions == -1)?true: ((this->Permissions & MainMenueChoice) == MainMenueChoice);
	 }

	enum enSaveResult { svSavedSuccessfully, svFailedEmptyObject, svFailedAccountNumber };

	enSaveResult Save() {

		switch (this->_UserMod)
		{

		case _Empty:
			return svFailedEmptyObject;
			break;

		case _Update:
			_update();
			return svSavedSuccessfully;
			break;

		case _New:
			if (!isExistUser(this->_Username)) {
				_AddNew();
				this->_UserMod = _Update;
				return svSavedSuccessfully;
			}
			else {
				return svFailedAccountNumber;
			}
			break;

		case _Delete:
			if (isExistUser(this->_Username)) {
				_delete();
				return svSavedSuccessfully;
				break;
			}
	
		}
	}









	
	
};

