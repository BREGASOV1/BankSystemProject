#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include"clsString.h"
using namespace std;
class clsCurrency
{
private:
	enum enMode{ _Empty = 1, _Update};
	string _CountryName;
	string _CurrencyCode;
	string _CurrencyName;
	float _CurrencyRate;
	enMode _CurrencyMode;

	static clsCurrency _GetEmpty() {
		return clsCurrency(_Empty,"","", "", 0);
	} 


	static clsCurrency _ConvertLineToCurrency(string line) {
		
		vector<string> vCurrency = clsString::SplitString(line, "#//#");
		return clsCurrency(_Update,vCurrency[0], vCurrency[1], vCurrency[2], stof(vCurrency[3]));
	}
	
	static vector <clsCurrency > _StoreCurrencyFileInVector() {
		vector<clsCurrency> vCurrencies;
		fstream File;
		string line;
		File.open("RequiredFiles/Currencies.txt", ios::in);
		if (File.is_open()) {
			while (getline(File, line)) {
				if (line != "")
					vCurrencies.push_back(_ConvertLineToCurrency(line));

			}
		}
		File.close();
		return vCurrencies;
	}
	
	string _ConvertCurrencyToLine() {

		string line = "";
		line += _CountryName + "#//#";
		line += _CurrencyCode + "#//#";
		line += _CurrencyName + "#//#";
		line += to_string(_CurrencyRate);
		return line;
	}

	void _StoreVectorOfCurrenciesInFile(vector <clsCurrency> vCurrencies) {
		fstream File;
		File.open("RequiredFiles/Currencies.txt", ios::out);
		if (File.is_open()) {
			for (clsCurrency& Currency : vCurrencies) 
				File << Currency._ConvertCurrencyToLine() << endl;
			
		
		}
		File.close();
	}

public:

	clsCurrency(enMode Mode, string CountryName, string CountryCode, string CurrencyName, float CurrencyRate) {
		_CurrencyMode = Mode;
		_CountryName = CountryName;
		_CurrencyCode = CountryCode;
		_CurrencyName = CurrencyName;
		_CurrencyRate = CurrencyRate;
	}

	
	float GetCurrencyRate() {
		return _CurrencyRate;
	}
	

	string GetCountryName() {
		return _CountryName;
	}

	string GetCurrencyCode() {
		return _CurrencyCode;
	}

	string GetCurrencyName() {
		return _CurrencyName;
	}

	clsCurrency FindWithCountryName(string CountryName) {
		vector<clsCurrency> vCurrencies = _StoreCurrencyFileInVector();
		for (clsCurrency& Currency : vCurrencies) {
			if (clsString::LowerOrUpperString('L',Currency.GetCountryName()) == clsString::LowerOrUpperString('L', CountryName)) {
				Currency._CurrencyMode = _Update;
				return Currency;
			
			}
		}
		return _GetEmpty();

	}

	static clsCurrency FindWithCurrencyCode(string CountryCode) {
		vector<clsCurrency> vCurrencies = _StoreCurrencyFileInVector();
		for (clsCurrency& Currency : vCurrencies) {
			if (clsString::LowerOrUpperString('L', Currency.GetCurrencyCode()) == clsString::LowerOrUpperString('L', CountryCode)) {
				Currency._CurrencyMode = _Update;
				return Currency;
				
			}
		}
		return _GetEmpty();

	}

	void Save() {
		
		vector<clsCurrency> vCurrencies = _StoreCurrencyFileInVector();
		for (clsCurrency& Currency : vCurrencies) {
			if (Currency.GetCurrencyCode() == _CurrencyCode && Currency._CurrencyMode  == _Update) {
				Currency = *this;
				break;
			}
		}
		_StoreVectorOfCurrenciesInFile(vCurrencies);
	}

	bool UpdateRate(float NewRate) {
		if (NewRate > 0) {
			_CurrencyRate = NewRate;
			this->Save();
			return true;
		}
		else
			return false;
	}

	static  bool isExistCurrency(string CurrencyCode) {
		 return (!FindWithCurrencyCode(CurrencyCode).isEmpty());
	}

	 bool isEmpty() {
		 return(_CurrencyMode == _Empty);
	 }

	static vector<clsCurrency>  GetCurrenciesList() {
		return _StoreCurrencyFileInVector();
	}

	static bool isCurrencyCodeUSD(string CurrencyCode) {
		return (CurrencyCode == "USD");
	}

	
	float CalculateCurrencyToUSD(float amount) {
		return(float) (amount / this->GetCurrencyRate());
	}
	float CalculateCurrencyTo(clsCurrency ToCurrency, float amount) {

		if (ToCurrency.GetCurrencyCode() == "USD")
			return  CalculateCurrencyToUSD(amount);
		else {
			amount = amount / this->GetCurrencyRate();
			return (float)(amount * ToCurrency.GetCurrencyRate());
		}
	}
};

