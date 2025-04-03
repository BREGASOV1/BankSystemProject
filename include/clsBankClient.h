#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<iomanip>
#include<string>
#include"clsPerson.h"
#include"clsString.h"
#include"clsDate.h"
using namespace std;
class clsBankClient:public clsPerson
{
private:

	enum enClientMod { _Empty = 0 , _Update , _New, _Delete};

	string _AccountNumber;
	string _PIN;
	double _Balance;
	enClientMod _ClientMod;
	string _TransferDate;


	static clsBankClient _EmptyClient() {
		return clsBankClient(_Empty, "", "", "", "", "", "", 0);
	}

    static clsBankClient _ConvertLineToClient(string line) {

		vector <string> vClientData = clsString::SplitString(line, "#//#");
		vClientData[5] = clsUtility::DecryptText(vClientData[5], 15);
		return clsBankClient(_Update,vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
			
	}
	 
	static vector<clsBankClient> _StoreFileInClientVector() {
		fstream File;
		vector<clsBankClient> vClients;
		string line;
		File.open("Clients.txt", ios::in);
		if (File.is_open()) {
			while (getline(File, line))
			{
				if (line != "")
					vClients.push_back(_ConvertLineToClient(line));

			}
		}
		File.close();
		return vClients;
	}

	string _ConvertTransferProcessToLine(clsBankClient SenderClient, clsBankClient ReceiverClient, double amount) {
		string line = "";
		line += clsDate::DateToString(clsDate()) + " - ";
		line += clsDate::GetSystemTime() + "#//#";
		line += SenderClient.GetAccountNumber() + "#//#";
		line += ReceiverClient.GetAccountNumber() + "#//#";
		line += to_string(amount) + "#//#";
		line += to_string(SenderClient.Balance) + "#//#";
		line += to_string(ReceiverClient.Balance) + "#//#";
		line += CurrentUser.Username;
		return line;
	}


	string _ConvertClientRecordIntoLine(clsBankClient Client) {
		string line = "";
		line += Client.FirstName + "#//#";
		line += Client.LastName + "#//#";
		line += Client.Email + "#//#";
		line += Client.Phone + "#//#";
		line += Client._AccountNumber + "#//#";
		line += clsUtility::EncryptText(Client.PIN,15) + "#//#";
		line += to_string(Client.Balance);
		return line;
	}

	void _StoreVectorOfClientsInFile(vector<clsBankClient> vClients) {
		fstream File;
		File.open("Clients.txt", ios::out);
		if (File.is_open()) {
			for (clsBankClient Client : vClients)
			{
				if (Client._ClientMod != _Empty && Client._ClientMod != _Delete)
					File << _ConvertClientRecordIntoLine(Client) << endl;
			}
		}
		File.close();

	}


	void _update() {
		vector<clsBankClient> vClients = _StoreFileInClientVector();
		for (clsBankClient& Client : vClients) {
			if (Client._AccountNumber == this->_AccountNumber) {
				Client = *this;
				break;
			}
		}
		
		_StoreVectorOfClientsInFile(vClients);
	}

	void _delete() {
			 vector<clsBankClient> vClients = _StoreFileInClientVector();
			 for (clsBankClient& Client : vClients) {
				 if (Client._AccountNumber == this->_AccountNumber) {
					 Client = *this;
					 break;
				 }
			 }
			 *this = _EmptyClient();
			 _StoreVectorOfClientsInFile(vClients);
		 
	 } 
	
	void _AddNew() {
		 string NewClient = _ConvertClientRecordIntoLine(*this);
		 fstream File;
		 File.open("Clients.txt", ios::app);
		 if (File.is_open()) {
			 if (NewClient != "")
				 File << NewClient << endl;
		 }
		 File.close();
	 }


public:

	struct stTransferLog{
		string SenderAccountNumber;
		string ReceiverAccountNumber;
		string TransferDateTime;
		string username;
		double amount;
		double SenderNewBalance;
		double ReceiverNewBalance;

	};

	clsBankClient(enClientMod ClientMod, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PIN, double Balance)
		:clsPerson(FirstName, LastName, Email, Phone) {
		_AccountNumber = AccountNumber;
		_PIN = PIN;
		_Balance = Balance;
		_ClientMod = ClientMod;
	}


	void SetPIN(string PIN) {
		_PIN = PIN;
	}
	string GetPIN() {
		return _PIN;
	}
	__declspec(property(get = GetPIN, put = SetPIN))string PIN;


	void SetBalance(double balance) {
		_Balance = balance;
	}
	double GetBalance() {
		return _Balance;
	}
	__declspec(property(get = GetBalance, put = SetBalance))double Balance;

	string GetAccountNumber() {
		return _AccountNumber;
	}


	 void MarkClientToDelete() {

		this->_ClientMod = _Delete;

	}

	
	bool _isEmpty() {
		return (_ClientMod == _Empty);
	}


	static clsBankClient CreatNewClient(string AccountNumber) {
		return clsBankClient(_New, "", "", "", "", AccountNumber, "", 0);
	}

	static clsBankClient Find(string AccountNumber) {
		vector <clsBankClient> vClients;
		fstream File;
		string line;
		File.open("Clients.txt", ios::in); 
		bool temp = File.is_open();
		if (File.is_open()) {
			while (getline(File, line)) {
				clsBankClient Client = _ConvertLineToClient(line);
				if (Client.GetAccountNumber() == AccountNumber) {
					File.close();
					return Client;
				}
				vClients.push_back(Client);

			}
		}
			File.close();
			return _EmptyClient();
			
		
		}

	static clsBankClient Find(string AccountNumber,string PIN) {
		vector <clsBankClient> vClients;
		fstream File;
		string line;
		File.open("Clients.txt", ios::in);
		if (File.is_open())
			while (getline(File, line)) {
				clsBankClient Client = _ConvertLineToClient(line);
				if (Client.GetAccountNumber() == AccountNumber && Client.PIN == PIN) {
					File.close();
					return Client;
				}
				vClients.push_back(Client);

			}
		File.close();
		return _EmptyClient();


	}

    static  bool isExistClient(string AccountNumber) {
		 clsBankClient Client = clsBankClient::Find(AccountNumber);
		 return !(Client._isEmpty());
			 
    	}

	static vector<clsBankClient> GetClientList() {
		return _StoreFileInClientVector();
	}
	
	static double TotalBalances() {
		double Total = 0;
		vector<clsBankClient> vClients = _StoreFileInClientVector();
		for (clsBankClient& Client : vClients)
			Total += Client.Balance;
		return Total;
	}

	static short ClientsCount() {
		return GetClientList().size();
		
	}
	
	string GetFullName() {
		return FirstName + " " + LastName;
	}

	void Deposit(double value) {
		_Balance += value;
	}

	bool Withdrawl(double value) {
		if (value <= _Balance) {
			_Balance -= value;
			return true;
		}
		else
			return false;
	}


	bool TransferTo(double amount, clsBankClient& ReceiverClient) {
		if (amount > Balance)
			return false;
		else
		{
			ReceiverClient.Deposit(amount);
			Withdrawl(amount);
			this->Save();
			ReceiverClient.Save();
			SaveTransferInLogFile(*this, ReceiverClient, amount);
			return true;

		}
	}


	static stTransferLog ConvertLineToTransferLog(string line) {
		vector <string> vTransferLog = clsString::SplitString(line, "#//#");
		stTransferLog TransferLog;

		TransferLog.TransferDateTime = vTransferLog[0];
		TransferLog.SenderAccountNumber = vTransferLog[1];
		TransferLog.ReceiverAccountNumber = vTransferLog[2];
		TransferLog.amount = stod(vTransferLog[3]);
		TransferLog.SenderNewBalance = stod(vTransferLog[4]);
		TransferLog.ReceiverNewBalance = stod(vTransferLog[5]);
		TransferLog.username = vTransferLog[6];

		return TransferLog;
	}

	static vector<stTransferLog> StoreTransferLogFileInVector() {
		vector<stTransferLog> vLoginRegisters;
		fstream File;
		string line;
		File.open("TransfersLog.txt", ios::in);
		while (getline(File, line)) {
			if (line != "")
				vLoginRegisters.push_back(ConvertLineToTransferLog(line));
		}
		File.close();
		return vLoginRegisters;

	}

	static vector<stTransferLog> GetTransfersLog() {
		return StoreTransferLogFileInVector();
	}





	void SaveTransferInLogFile(clsBankClient SenderClient, clsBankClient ReceiverClient, double amount) {
		string line = _ConvertTransferProcessToLine(SenderClient,ReceiverClient,amount);
		fstream File;
		File.open("TransfersLog.txt", ios::out | ios::app);
		if (File.is_open()) {
			if (line != "")
				File << line << endl;
		}

		File.close();

	}

	enum enSaveResult {svSavedSuccessfully, svFailedEmptyObject, svFailedAccountNumber};

	enSaveResult Save() {

		switch (this->_ClientMod)
		{

		case _Empty:
			return svFailedEmptyObject;
			break;

		case _Update:
			_update();
			return svSavedSuccessfully;
			break;

		case _New:
			if (!isExistClient(this->_AccountNumber)) {
				_AddNew();
				this->_ClientMod = _Update;
				return svSavedSuccessfully;
			}
			else {
				return svFailedAccountNumber;
			}
			break;

		case _Delete:
			if (isExistClient(this->_AccountNumber)) {
				_delete();
				return svSavedSuccessfully;
				break;
			}
			else if (_isEmpty()) {
				return svFailedEmptyObject;
				break;
			}
			else {
				return svFailedAccountNumber;
				break;

			}
		}
	}
	

};

